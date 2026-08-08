#pragma once

#include "geometry/Mesh.h"
#include "textures/Texture.h"
#include "renderer/Renderer.h"
#include "components/Material.h"

class CRT {
public:
  static void load(Scene &scene, const std::string &path);
  static void load(Camera &camera, const std::string &path);
  static void load(EntityManager &em, const std::string &path);
  static void load(Renderer &renderer, const std::string &path);

  static std::shared_ptr<Mesh> loadMesh(const std::string &path, int idx = 0);
  static std::shared_ptr<Texture> loadTexture(const std::string &path, int idx = 0);
  static std::shared_ptr<Material> loadMaterial(const std::string &path, int idx = 0);

private:
  struct Schema {
    std::string path;

    struct {
      std::vector<float> background_color;
      std::vector<int> image_settings;
    } settings;

    struct {
      std::vector<float> matrix;
      std::vector<float> position;
    } camera;

    struct Light {
      float intensity = -1;
      std::vector<float> position;
    };
    std::vector<Light> lights;

    struct Texture {
      float edge_width = 0.1, square_size = 1;
      std::string name, type = "albedo", file_path;
      std::vector<float> albedo, color_A, color_B, edge_color, inner_color;
    };
    std::vector<Texture> textures;

    struct Material {
      float ior = 1.5;
      std::vector<float> albedo;
      bool smooth_shading = true;
      std::string type = "diffuse", texture_name;
    };
    std::vector<Material> materials;

    struct Object {
      int material_index = -1;
      std::vector<float> uvs, vertices;
      std::vector<unsigned int> triangles;
    };
    std::vector<Object> objects;
  };

  static Schema parse(const std::string &path);

  static void load(Scene &scene, const Schema &schema);
  static void load(Camera &camera, const Schema &schema);
  static void load(EntityManager &em, const Schema &schema);
  static void load(Renderer &renderer, const Schema &schema);

  static std::shared_ptr<Mesh> loadMesh(const Schema &schema, int idx = 0);
  static std::shared_ptr<Texture> loadTexture(const Schema &schema, int idx = 0);
  static std::shared_ptr<Material> loadMaterial(const Schema &schema, int idx = 0);

  static Vec3 toVec3(const std::vector<float> &a);
  static Color toColor(const std::vector<float> &a);
};
