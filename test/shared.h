#ifndef SHARED_H
#define SHARED_H

#include "io/IO.h"

constexpr bool RENDER_FAST_PLZ = true;
constexpr int IMAGE_WIDTH = RENDER_FAST_PLZ ? 320 : 1280;
constexpr int IMAGE_HEIGHT = RENDER_FAST_PLZ ? 180 : 720;
constexpr int RENDERER_SAMPLES_PER_PIXEL = RENDER_FAST_PLZ ? 5 : 10;
constexpr int RENDERER_MAX_DEPTH = 10;

EntityId createLight(Scene &scene, const std::vector<std::shared_ptr<Component>> &components);
EntityId drawQuad(Scene &scene, const std::vector<std::shared_ptr<Component>> &components);
EntityId drawSphere(Scene &scene, const std::vector<std::shared_ptr<Component>> &components);
EntityId drawCube(Scene &scene, const std::vector<std::shared_ptr<Component>> &components);
EntityId drawTriangle(Scene &scene, const std::vector<std::shared_ptr<Component>> &components);
EntityId loadModel(Scene &scene, const std::string &path, IO::FileFormat format);

#endif

#if defined(SHARED_IMPLEMENTATION) && !defined(SHARED_IMPLEMENTAION_GUARD)
#define SHARED_IMPLEMENTATION_GUARD

#include "geometry/Quad.h"
#include "geometry/Sphere.h"
#include "components/Hierarchy.h"

constexpr const char *CUBE_FILE_PATH = "./assets/models/cube.obj";
constexpr IO::FileFormat CUBE_FILE_FORMAT = IO::FileFormat::OBJ;

EntityId createLight(Scene &scene, const std::vector<std::shared_ptr<Component>> &components) {
  auto lights = scene.getLights();
  auto &em = scene.getEntityManager();

  if (em.has<Hierarchy>(lights)) {
    auto light = em.createEntity();
    em.setAll(light, components);

    auto hierarchy = em.get<Hierarchy>(lights);
    hierarchy->add(light);

    return light;
  }

  return EntityManager::NIL;
}

EntityId drawQuad(Scene &scene, const std::vector<std::shared_ptr<Component>> &components) {
  auto &em = scene.getEntityManager();
  auto quad = em.createEntity();
  em.setAll(quad, components);

  auto geometry = std::make_shared<Quad>();
  em.set(quad, geometry);
  return quad;
}

EntityId drawSphere(Scene &scene, const std::vector<std::shared_ptr<Component>> &components) {
  auto &em = scene.getEntityManager();
  auto sphere = em.createEntity();
  em.setAll(sphere, components);

  auto sdf = std::make_shared<Sphere>();
  em.set(sphere, sdf);
  return sphere;
}

EntityId drawCube(Scene &scene, const std::vector<std::shared_ptr<Component>> &components) {
  auto &em = scene.getEntityManager();
  auto cube = loadModel(scene, CUBE_FILE_PATH, CUBE_FILE_FORMAT);
  em.setAll(cube, components);
  return cube;
}

EntityId drawTriangle(Scene &scene, const std::vector<std::shared_ptr<Component>> &components) {
  auto &em = scene.getEntityManager();
  auto triangle = em.createEntity();
  em.setAll(triangle, components);

  std::vector<unsigned int> indices = {0, 1, 2};
  std::vector<Vertex> vertices = {
      {
          .normal = Vec3(0, 0, 1),
          .position = Vec3(-1, -1, 0),
      },
      {

          .normal = Vec3(0, 0, 1),
          .position = Vec3(1, -1, 0),
      },
      {
          .normal = Vec3(0, 0, 1),
          .position = Vec3(0, 1, 0),
      },
  };

  auto mesh = std::make_shared<Mesh>(vertices, indices);
  em.set(triangle, mesh);
  return triangle;
}

EntityId loadModel(Scene &scene, const std::string &path, IO::FileFormat format) {
  auto &em = scene.getEntityManager();
  auto model = em.createEntity();

  auto mesh = std::make_shared<Mesh>();
  IO::load(*mesh, path, format);
  em.set(model, mesh);
  return model;
}

#endif
