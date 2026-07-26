#include <memory>
#include <vector>
#include <iostream>

#include "utils/string.h"
#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"

#include "skybox/Sky.h"
#include "entity/Entity.h"
#include "geometry/Vector.h"
#include "geometry/Vertex.h"
#include "components/Mesh.h"
#include "materials/Lambertian.h"

#include "io/CRT.h"

void CRT::load(Scene &scene, const std::string &path) {
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
        auto skybox = std::make_shared<Sky>();
        skybox->setEndColor(Color(a[0], a[1], a[2], 1));
        scene.setSkybox(skybox);
      }
    }
  }

  if (!document.HasMember("camera")) {
    std::cout << "Member does not exist: camera" << std::endl;
  } else {
    auto &sceneCam = scene.getCamera();
    auto camera = document["camera"].GetObject();
    std::cout << "Found camera" << std::endl;

    if (!camera.HasMember("matrix")) {
      std::cout << "Member does not exist: matrix" << std::endl;
    } else {
      auto matrix = camera["matrix"].GetArray();
      std::cout << "Found camera matrix" << std::endl;
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
        sceneCam.setPosition(Vec3(p[0], p[1], p[2]));
        std::cout << "Set camera position" << std::endl;
      }
    }
  }

  if (!document.HasMember("objects")) {
    std::cout << "Member does not exist: objects" << std::endl;
  } else {
    auto &em = scene.getEntityManager();
    auto objects = document["objects"].GetArray();
    std::cout << "Found " << objects.Size() << " objects" << std::endl;

    auto mat = std::make_shared<Lambertian>(COLOR_GREY);

    for (rapidjson::SizeType i = 0; i < objects.Size(); i++) {
      if (!objects[i].HasMember("triangles")) {
        std::cout << "Member does not exist: triangles" << std::endl;
        continue;
      }

      if (!objects[i].HasMember("vertices")) {
        std::cout << "Member does not exist: vertices" << std::endl;
        continue;
      }

      auto indices = objects[i]["triangles"].GetArray();
      if (indices.Size() % 3 != 0) {
        std::cout << "Indices array size not divisible by 3" << std::endl;
        continue;
      }
      std::cout << "Found " << indices.Size() / 3 << " triangles" << std::endl;

      auto vertices = objects[i]["vertices"].GetArray();
      if (vertices.Size() % 3 != 0) {
        std::cout << "Indices array size not divisible by 3" << std::endl;
        continue;
      }
      std::cout << "Found " << vertices.Size() / 3 << " vertices" << std::endl;

      std::vector<Vertex> meshVertices;
      std::vector<unsigned int> meshIndices;

      std::cout << "indices: ";
      for (rapidjson::SizeType j = 0; j < indices.Size(); j++) {
        auto idx = indices[j].GetInt();
        std::cout << idx << " ";
        meshIndices.push_back(idx);
      }
      std::cout << std::endl;

      std::cout << "vertices: ";
      for (rapidjson::SizeType j = 0; j < vertices.Size(); j += 3) {
        Vec3 p(vertices[j].GetFloat(), vertices[j + 1].GetFloat(), vertices[j + 2].GetFloat());
        std::cout << p << " ";

        Vertex v;
        v.position = p;
        meshVertices.push_back(v);
      }
      std::cout << std::endl;

      for (int j = 0; j < meshIndices.size(); j += 3) {
        Vec3 a = meshVertices[meshIndices[j + 1]].position - meshVertices[meshIndices[j]].position;
        Vec3 b = meshVertices[meshIndices[j + 2]].position - meshVertices[meshIndices[j]].position;

        Vec3 n = cross(a, b);
        meshVertices[meshIndices[j]].normal = n;
        meshVertices[meshIndices[j + 1]].normal = n;
        meshVertices[meshIndices[j + 2]].normal = n;
      }
      auto mesh = std::make_shared<Mesh>(meshVertices, meshIndices);

      EntityId eId = em.createEntity();
      em.setAll(eId, {mat, mesh});
    }
  }
}
