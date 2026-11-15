#include "WipeManager.h"

#include "GridWipe.h"

WipeManager::WipeManager() = default;

WipeManager::~WipeManager() = default;

void WipeManager::Update() {
	if (m_current_wipe) {
		m_current_wipe->Update();
	}
}

void WipeManager::Draw() {
	if (m_current_wipe) {
		m_current_wipe->Draw();
	}
}

void WipeManager::Start(WipeType type, WipeState state, float duration, uint32_t texture_handle) {
	switch (type) {
		using enum WipeType;
	case TYPE_GRID: {
		auto gridWipe = std::make_unique<GridWipe>();
		gridWipe->Initialize(texture_handle);
		m_current_wipe = std::move(gridWipe);
		break;
	}
	}

	if (m_current_wipe) {
		m_current_wipe->Start(state, duration);
	}
}

bool WipeManager::IsFinished() const { return m_current_wipe ? m_current_wipe->IsFinished() : true; }
