#include "flutter/shell/platform/tizen/flutter_tizen_engine_group.h"

namespace flutter {

FlutterTizenEngine* FlutterTizenEngineGroup::MakeEngineWithProject(
    const FlutterProjectBundle& project) {
  std::unique_ptr<FlutterTizenEngine> engine =
      std::make_unique<flutter::FlutterTizenEngine>(project);
  engine->SetEngineName(std::string("FlutterTizenEngine") +
                        std::to_string(engines_.size()));

  engines_.push_back(std::move(engine));

  return engines_.back().get();
}

FlutterTizenEngine* FlutterTizenEngineGroup::GetEngineSpawner() {
  return engines_[0].get();
}

int FlutterTizenEngineGroup::GetEngineCount() {
  return engines_.size();
}

void FlutterTizenEngineGroup::RemoveEngine(FlutterTizenEngine* engine) {
  if (engine) {
    for (auto iter = engines_.begin(); iter != engines_.end(); ++iter) {
      if (engine->name() == iter->get()->name()) {
        engine->StopEngine();
        engines_.erase(iter);
        return;
      }
    }
  }
}

}  // namespace flutter