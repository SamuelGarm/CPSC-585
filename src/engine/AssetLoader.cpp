#include "engine/AssetLoader.hpp"
#include <thread>
#include <iostream>

AssetLoader g_Assets;

void AssetLoader::loadAsset(Asset asset)
{
  std::string path = asset.filepath;
  std::string name = asset.name;
  switch (asset.type)
  {
  case MODEL:
    m_renderables[name] = RenderModel();
    GraphicsSystem::importOBJ(m_renderables[name], path);
    break;
  case SPLINE:
    m_geoms[name] = CPU_Geometry();
    GraphicsSystem::importSplineFromOBJ(m_geoms[name], path);
    break;
  case COLLIDER:
    m_geoms[name] = CPU_Geometry();
    GraphicsSystem::importOBJ(m_geoms[name], path);
    break;
  }
}

/*
* this thread spins off other threads for each asset to load them
* when it is finished it cleans up and returns
*/
void AssetLoader::loadAssets()
{

  std::vector<std::thread> loadingThreads;
  // load the asset into the asset map
  for (auto& asset : m_registered)
  {
    std::thread t(&AssetLoader::loadAsset, this, asset); // spawn a new thread

    loadingThreads.push_back(move(t));
  }

  // join up all the loaders
  for (auto& thread : loadingThreads)
  {
    thread.join();
  }
  std::cout << "all assets loaded!\n";

}

/*
* When it is done all threads are joined and the thread ends
*/
void AssetLoader::loadAsyncWorker(void (*when_complete)())
{
  // this will be spawned on seperate thread, which will load assets
  // then call the provided callback
  std::thread i_want_to_kms = std::thread(&AssetLoader::loadAssets, this);
  i_want_to_kms.join();
  when_complete();
}

/*
* begin the process of loading assets in the background.
* This will spin up a new thread to handle the threads so the main thread can keep doing stuff while this runs
*/
void AssetLoader::loadAssetsAsync(void (*when_complete)())
{
  std::thread loader = std::thread(&AssetLoader::loadAsyncWorker, this, when_complete);
  loader.detach();
}
void AssetLoader::loadAssetsAsync()
{
  auto doNothing = [] {};
  std::thread loader = std::thread(&AssetLoader::loadAsyncWorker, this, doNothing);
  loader.detach();

}



CPU_Geometry& AssetLoader::getSpline(std::string name)
{
  return m_geoms[name];
}

CPU_Geometry& AssetLoader::getColliderGeometry(std::string name)
{
  return m_geoms[name];
}

RenderModel& AssetLoader::getRenderModel(std::string name)
{
  return m_renderables[name];
}

