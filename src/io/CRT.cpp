#include <memory>
#include <vector>
#include <iostream>

#include "utils/string.h"
#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"

#include "io/IO.h"
#include "geometry/Quad.h"
#include "components/Hierarchy.h"

#include "textures/Edge.h"
#include "textures/SolidColor.h"
#include "textures/CheckerBoard.h"

#include "materials/Metal.h"
#include "materials/Emissive.h"
#include "materials/Lambertian.h"
#include "materials/Dielectric.h"

#include "io/CRT.h"

void CRT::load(Scene &scene, const std::string &path) {
  Schema schema = parse(path);
  load(scene, schema);
}

void CRT::load(Scene &scene, const Schema &schema) {
  auto &camera = scene.getCamera();
  load(camera, schema);

  auto &em = scene.getEntityManager();
  load(em, schema);

  if (schema.settings.background_color.size() > 0) {
    auto skybox = std::make_shared<Sky>();
    skybox->setEndColor(toColor(schema.settings.background_color));
    scene.setSkybox(skybox);
  }

  auto lights = scene.getLights();
  if (em.has<Hierarchy>(lights)) {
    auto hierarchy = em.get<Hierarchy>(lights);

    for (auto &light : schema.lights) {
      if (light.intensity > 0) {
        auto eId = em.createEntity();
        auto mat = std::make_shared<Emissive>(clamp(light.intensity, 0, 1) * COLOR_WHITE);
        auto transform = std::make_shared<Transform>(toVec3(light.position));
        em.setAll(eId, {mat, transform});
        hierarchy->add(eId);
      }
    }
  }
}

void CRT::load(Camera &camera, const std::string &path) {
  Schema schema = parse(path);
  load(camera, schema);
}

void CRT::load(Camera &camera, const Schema &schema) {
  if (schema.camera.position.size() > 0) {
    camera.setPosition(toVec3(schema.camera.position));
  }
}

void CRT::load(EntityManager &em, const std::string &path) {
  Schema schema = parse(path);
  load(em, schema);
}

void CRT::load(EntityManager &em, const Schema &schema) {
  for (int i = 0; i < schema.objects.size(); i++) {
    EntityId eId = em.createEntity();
    auto mesh = loadMesh(schema, i);
    auto mat = loadMaterial(schema, schema.objects[i].material_index);
    em.setAll(eId, {mesh, mat});
  }
}

void CRT::load(Renderer &renderer, const std::string &path) {
  Schema schema = parse(path);
  load(renderer, schema);
}

void CRT::load(Renderer &renderer, const Schema &schema) {
  if (schema.settings.image_settings.size() == 2) {
    std::vector<int> a = schema.settings.image_settings;
    renderer.setDimensions(a[0], a[1]);
  }
}

std::shared_ptr<Mesh> CRT::loadMesh(const std::string &path, int idx) {
  Schema schema = parse(path);
  return loadMesh(schema, idx);
}

std::shared_ptr<Mesh> CRT::loadMesh(const Schema &schema, int idx) {
  if (idx < 0 || idx >= schema.objects.size()) {
    return std::make_shared<Quad>();
  }

  std::vector<Vertex> meshVertices;
  std::vector<unsigned int> meshIndices;
  auto &uvs = schema.objects[idx].uvs;
  auto &vertices = schema.objects[idx].vertices;
  auto &triangles = schema.objects[idx].triangles;

  for (int i = 0; i < triangles.size(); i++) {
    meshIndices.push_back(triangles[i]);
  }
  for (int i = 0; i < vertices.size() / 3; i++) {
    Vertex v;
    v.texCoords = uvs.empty() ? 0 : Vec2(uvs[3 * i], uvs[3 * i + 1]);
    v.position = Vec3(vertices[3 * i], vertices[3 * i + 1], vertices[3 * i + 2]);
    meshVertices.push_back(v);
  }

  return std::make_shared<Mesh>(meshVertices, meshIndices);
}

std::shared_ptr<Texture> CRT::loadTexture(const std::string &path, int idx) {
  Schema schema = parse(path);
  return loadTexture(schema, idx);
}

std::shared_ptr<Texture> CRT::loadTexture(const Schema &schema, int idx) {
  if (idx < 0 || idx >= schema.textures.size()) {
    return std::make_shared<SolidColor>(COLOR_MAGENTA);
  }

  auto &type = schema.textures[idx].type;
  if (type == "albedo") {
    return std::make_shared<SolidColor>(toColor(schema.textures[idx].albedo));

  } else if (type == "checker") {
    float f = 1 / schema.textures[idx].square_size;
    auto cA = toColor(schema.textures[idx].color_A);
    auto cB = toColor(schema.textures[idx].color_B);
    return std::make_shared<CheckerBoard>(cA, cB, f, f);

  } else if (type == "edges") {
    float e = schema.textures[idx].edge_width;
    auto cE = toColor(schema.textures[idx].edge_color);
    auto cI = toColor(schema.textures[idx].inner_color);
    return std::make_shared<Edge>(cE, cI, e);

  } else if (type == "bitmap") {
    auto s = schema.path;
    while (s[s.length() - 1] != '/') {
      s = s.substr(0, s.length() - 1);
    }
    s = s.substr(0, s.length() - 1) + schema.textures[idx].file_path;

    return IO::loadImage(s, IO::PNG);
  }

  return std::make_shared<SolidColor>(COLOR_MAGENTA);
}

std::shared_ptr<Material> CRT::loadMaterial(const std::string &path, int idx) {
  Schema schema = parse(path);
  return loadMaterial(schema, idx);
}

std::shared_ptr<Material> CRT::loadMaterial(const Schema &schema, int idx) {
  if (idx < 0 || idx >= schema.materials.size()) {
    return std::make_shared<Lambertian>(COLOR_MAGENTA);
  }

  std::shared_ptr<Texture> texture = std::make_shared<SolidColor>(COLOR_MAGENTA);

  if (schema.materials[idx].albedo.size() > 0) {
    texture = std::make_shared<SolidColor>(toColor(schema.materials[idx].albedo));

  } else if (schema.materials[idx].texture_name.length() > 0) {
    for (int i = 0; i < schema.textures.size(); i++) {
      if (schema.textures[i].name == schema.materials[idx].texture_name) {
        texture = loadTexture(schema, i);
        break;
      }
    }
  }

  auto type = schema.materials[idx].type;
  if (type == "reflective") {
    return std::make_shared<Metal>(texture);
  } else if (type == "refractive") {
    return std::make_shared<Dielectric>(schema.materials[idx].ior);
  } else {
    return std::make_shared<Lambertian>(texture);
  }
}

CRT::Schema CRT::parse(const std::string &path) {
  Schema schema;
  schema.path = path;

  rapidjson::Document document;
  std::string json = readEntireFile(path);
  document.Parse(json.c_str());

  if (!document.HasMember("settings")) {
    std::cout << "Member does not exist: settings." << std::endl;
  } else {
    auto settings = document["settings"].GetObject();
    std::cout << "Found settings attribute." << std::endl;

    if (!settings.HasMember("background_color")) {
      std::cout << "Member does not exist: background_color." << std::endl;
    } else {
      auto backgroundColor = settings["background_color"].GetArray();
      std::cout << "Found background_color attribute." << std::endl;

      std::vector<float> a;
      for (rapidjson::SizeType i = 0; i < backgroundColor.Size(); i++) {
        a.push_back(backgroundColor[i].GetFloat());
      }

      if (a.size() != 3) {
        std::cout << "background_color doesnt have 3 components" << std::endl;
      } else {
        schema.settings.background_color = a;
      }
    }
  }

  if (!document.HasMember("camera")) {
    std::cout << "Member does not exist: camera" << std::endl;
  } else {
    auto camera = document["camera"].GetObject();
    std::cout << "Found camera" << std::endl;

    if (!camera.HasMember("matrix")) {
      std::cout << "Member does not exist: matrix" << std::endl;
    } else {
      auto matrix = camera["matrix"].GetArray();
      std::cout << "Found camera matrix" << std::endl;

      std::vector<float> a;
      for (rapidjson::SizeType i = 0; i < matrix.Size(); i++) {
        a.push_back(matrix[i].GetFloat());
      }

      if (a.size() != 9) {
        std::cout << "matrix doesnt have 9 components" << std::endl;
      } else {
        schema.camera.matrix = a;
        std::cout << "Set camera matrix" << std::endl;
      }
    }

    if (!camera.HasMember("position")) {
      std::cout << "Member does not exist: position" << std::endl;
    } else {
      auto position = camera["position"].GetArray();
      std::cout << "Found camera position" << std::endl;

      std::vector<float> p;
      for (rapidjson::SizeType i = 0; i < position.Size(); i++) {
        p.push_back(position[i].GetFloat());
      }

      if (p.size() != 3) {
        std::cout << "Camera position doesnt have 3 components" << std::endl;
      } else {
        schema.camera.position = p;
        std::cout << "Set camera position" << std::endl;
      }
    }
  }

  if (!document.HasMember("lights")) {
    std::cout << "Member does not exist: lights" << std::endl;
  } else {
    auto lights = document["lights"].GetArray();
    std::cout << "Found " << lights.Size() << " lights" << std::endl;

    for (rapidjson::SizeType i = 0; i < lights.Size(); i++) {
      Schema::Light light;

      if (!lights[i].HasMember("intensity")) {
        std::cout << "Member does not exist: intensity" << std::endl;
      } else {
        light.intensity = lights[i]["intensity"].GetFloat();
        std::cout << "Found light intensity" << std::endl;
      }

      if (!lights[i].HasMember("position")) {
        std::cout << "Member does not exist: position" << std::endl;
      } else {
        auto p = lights[i]["position"].GetArray();
        std::cout << "Found light position" << std::endl;

        if (p.Size() != 3) {
          std::cout << "Position vector has " << p.Size() << " components != 3" << std::endl;
        } else {
          for (int j = 0; j < p.Size(); j++) {
            light.position.push_back(p[j].GetFloat());
          }
        }
      }

      schema.lights.push_back(light);
    }
  }

  if (!document.HasMember("textures")) {
    std::cout << "Member does not exist: textures" << std::endl;
  } else {
    auto textures = document["textures"].GetArray();
    std::cout << "Found " << textures.Size() << " textures" << std::endl;

    for (rapidjson::SizeType i = 0; i < textures.Size(); i++) {
      Schema::Texture texture;

      if (!textures[i].HasMember("name")) {
        std::cout << "Member does not exist: name" << std::endl;
      } else {
        texture.name = textures[i]["name"].GetString();
        std::cout << "Found texture name" << std::endl;
      }

      if (!textures[i].HasMember("type")) {
        std::cout << "Member does not exist: type" << std::endl;
      } else {
        texture.type = textures[i]["type"].GetString();
        std::cout << "Found texture type" << std::endl;
      }

      if (!textures[i].HasMember("albedo")) {
        std::cout << "Member does not exist: albedo" << std::endl;
      } else {
        auto a = textures[i]["albedo"].GetArray();
        std::cout << "Found texture albedo" << std::endl;

        if (a.Size() != 3) {
          std::cout << "albedo vector has " << a.Size() << " components != 3" << std::endl;
        } else {
          for (int j = 0; j < a.Size(); j++) {
            texture.albedo.push_back(a[j].GetFloat());
          }
        }
      }

      if (!textures[i].HasMember("edge_color")) {
        std::cout << "Member does not exist: edge_color" << std::endl;
      } else {
        auto a = textures[i]["edge_color"].GetArray();
        std::cout << "Found texture edge_color" << std::endl;

        if (a.Size() != 3) {
          std::cout << "edge_color vector has " << a.Size() << " components != 3" << std::endl;
        } else {
          for (int j = 0; j < a.Size(); j++) {
            texture.edge_color.push_back(a[j].GetFloat());
          }
        }
      }

      if (!textures[i].HasMember("inner_color")) {
        std::cout << "Member does not exist: inner_color" << std::endl;
      } else {
        auto a = textures[i]["inner_color"].GetArray();
        std::cout << "Found texture inner_color" << std::endl;

        if (a.Size() != 3) {
          std::cout << "inner_color vector has " << a.Size() << " components != 3" << std::endl;
        } else {
          for (int j = 0; j < a.Size(); j++) {
            texture.inner_color.push_back(a[j].GetFloat());
          }
        }
      }

      if (!textures[i].HasMember("edge_width")) {
        std::cout << "Member does not exist: edge_width" << std::endl;
      } else {
        texture.edge_width = textures[i]["edge_width"].GetFloat();
        std::cout << "Found texture edge_width" << std::endl;
      }

      if (!textures[i].HasMember("color_A")) {
        std::cout << "Member does not exist: color_A" << std::endl;
      } else {
        auto a = textures[i]["color_A"].GetArray();
        std::cout << "Found texture color_A" << std::endl;

        if (a.Size() != 3) {
          std::cout << "color_A vector has " << a.Size() << " components != 3" << std::endl;
        } else {
          for (int j = 0; j < a.Size(); j++) {
            texture.color_A.push_back(a[j].GetFloat());
          }
        }
      }

      if (!textures[i].HasMember("color_B")) {
        std::cout << "Member does not exist: color_B" << std::endl;
      } else {
        auto a = textures[i]["color_B"].GetArray();
        std::cout << "Found texture color_B" << std::endl;

        if (a.Size() != 3) {
          std::cout << "color_B vector has " << a.Size() << " components != 3" << std::endl;
        } else {
          for (int j = 0; j < a.Size(); j++) {
            texture.color_B.push_back(a[j].GetFloat());
          }
        }
      }

      if (!textures[i].HasMember("square_size")) {
        std::cout << "Member does not exist: square_size" << std::endl;
      } else {
        texture.square_size = textures[i]["square_size"].GetFloat();
        std::cout << "Found texture square_size" << std::endl;
      }

      if (!textures[i].HasMember("file_path")) {
        std::cout << "Member does not exist: file_path" << std::endl;
      } else {
        texture.file_path = textures[i]["file_path"].GetString();
        std::cout << "Found texture file_path" << std::endl;
      }

      schema.textures.push_back(texture);
    }
  }

  if (!document.HasMember("materials")) {
    std::cout << "Member does not exist: materials" << std::endl;
  } else {
    auto materials = document["materials"].GetArray();
    std::cout << "Found " << materials.Size() << " materials" << std::endl;

    for (rapidjson::SizeType i = 0; i < materials.Size(); i++) {
      Schema::Material material;

      if (!materials[i].HasMember("type")) {
        std::cout << "Member does not exist: type" << std::endl;
      } else {
        material.type = materials[i]["type"].GetString();
        std::cout << "Found material type" << std::endl;
      }

      if (!materials[i].HasMember("albedo")) {
        std::cout << "Member does not exist: albedo" << std::endl;
      } else {
        auto &albedo = materials[i]["albedo"];

        if (albedo.IsString()) {
          material.texture_name = albedo.GetString();
        } else {
          auto p = albedo.GetArray();
          std::cout << "Found material albedo" << std::endl;

          if (p.Size() != 3) {
            std::cout << "albedo vector has " << p.Size() << " components != 3" << std::endl;
          } else {
            for (int j = 0; j < p.Size(); j++) {
              material.albedo.push_back(p[j].GetFloat());
            }
          }
        }
      }

      if (!materials[i].HasMember("smooth_shading")) {
        std::cout << "Member does not exist: smooth_shading" << std::endl;
      } else {
        material.smooth_shading = materials[i]["smooth_shading"].GetBool();
        std::cout << "Found material smooth_shading" << std::endl;
      }

      if (!materials[i].HasMember("ior")) {
        std::cout << "Member does not exist: ior" << std::endl;
      } else {
        material.ior = materials[i]["ior"].GetFloat();
        std::cout << "Found material ior" << std::endl;
      }

      schema.materials.push_back(material);
    }
  }

  if (!document.HasMember("objects")) {
    std::cout << "Member does not exist: objects" << std::endl;
  } else {
    auto objects = document["objects"].GetArray();
    std::cout << "Found " << objects.Size() << " objects" << std::endl;

    for (rapidjson::SizeType i = 0; i < objects.Size(); i++) {
      Schema::Object object;

      if (!objects[i].HasMember("material_index")) {
        std::cout << "Member does not exist: material_index" << std::endl;
      } else {
        object.material_index = objects[i]["material_index"].GetInt();
        std::cout << "Found object material_index" << std::endl;
      }

      if (!objects[i].HasMember("uvs")) {
        std::cout << "Member does not exist: uvs" << std::endl;
      } else {
        auto uvs = objects[i]["uvs"].GetArray();

        if (uvs.Size() % 3 != 0) {
          std::cout << "uvs array size not divisible by 3" << std::endl;
        } else {
          for (rapidjson::SizeType j = 0; j < uvs.Size(); j++) {
            object.uvs.push_back(uvs[j].GetFloat());
          }
        }
      }

      if (!objects[i].HasMember("triangles")) {
        std::cout << "Member does not exist: triangles" << std::endl;
      } else {
        auto triangles = objects[i]["triangles"].GetArray();

        if (triangles.Size() % 3 != 0) {
          std::cout << "triangles array size not divisible by 3" << std::endl;
        } else {
          for (rapidjson::SizeType j = 0; j < triangles.Size(); j++) {
            object.triangles.push_back(triangles[j].GetUint());
          }
        }
      }

      if (!objects[i].HasMember("vertices")) {
        std::cout << "Member does not exist: vertices" << std::endl;
      } else {
        auto vertices = objects[i]["vertices"].GetArray();

        if (vertices.Size() % 3 != 0) {
          std::cout << "vertices array size not divisible by 3" << std::endl;
        } else {
          for (rapidjson::SizeType j = 0; j < vertices.Size(); j++) {
            object.vertices.push_back(vertices[j].GetFloat());
          }
        }
      }

      schema.objects.push_back(object);
    }
  }

  return schema;
}

Vec3 CRT::toVec3(const std::vector<float> &a) {
  if (a.size() < 3) {
    return 0;
  } else {
    return Vec3(a[0], a[1], a[2]);
  }
}

Color CRT::toColor(const std::vector<float> &a) {
  if (a.size() < 3) {
    return 0;
  } else if (a.size() == 3) {
    return Color(a[0], a[1], a[2], 1);
  } else {
    return Color(a[0], a[1], a[2], a[3]);
  }
}
