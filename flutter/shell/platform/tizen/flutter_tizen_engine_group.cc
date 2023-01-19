#include "flutter/shell/platform/tizen/flutter_tizen_engine_group.h"

#include <random>

namespace flutter {

FlutterTizenEngine* FlutterTizenEngineGroup::MakeEngineWithProject(
    const FlutterProjectBundle& project) {
  std::unique_ptr<FlutterTizenEngine> engine =
      std::make_unique<flutter::FlutterTizenEngine>(project);

  static std::random_device random_device;
  static std::mt19937 generator(random_device());
  static std::uniform_int_distribution<uint32_t> distribution(0, 99999);

  engine->SetId(distribution(generator));

  engines_.push_back(std::move(engine));
  return engines_.back().get();
}

FlutterTizenEngine* FlutterTizenEngineGroup::GetEngineSpawner() {
  return engines_[0].get();
}

int FlutterTizenEngineGroup::GetEngineCount() {
  return engines_.size();
}

void FlutterTizenEngineGroup::StopEngine(uint32_t id) {
  for (auto it = engines_.begin(); it != engines_.end(); ++it) {
    if (id == it->get()->id()) {
      it->get()->StopEngine();
      engines_.erase(it);
      return;
    }
  }
}

}  // namespace flutter
