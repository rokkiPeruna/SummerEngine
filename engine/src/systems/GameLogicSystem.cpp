#include <systems/GameLogicSystem.h>
#include <AddLogicToEngine.h>

namespace se
{

CGameLogic* GetGameLogicComponent(SEint index)
{
	return &priv::GameLogicSystem::m_engine_ptr->GetGameLogicSystem().m_cGameLogic.at(index);

}

void RegisterEventHandle(EventHandler*& eventHandler)
{
	priv::GameLogicSystem::m_engine_ptr->GetEventManager().RegisterEventHandler(eventHandler);
	assert(eventHandler);
}


namespace priv
{
GameLogicSystem::GameLogicSystem(Engine& engine_ref)
	: ComponentSystem(engine_ref)
	, m_game_logic_names{}
	, m_cGameLogic{}
	, m_free_cGameLogic_indices{}
{
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::GAMELOGIC, this);
}

GameLogicSystem::~GameLogicSystem()
{
	
}

void GameLogicSystem::Initialize()
{
	LogicsFactory::GetInstance();


	m_engine.GetEventManager().RegisterEventHandler(m_event_handler);
	assert(m_event_handler);

	m_event_handler->RegisterEvent(SE_Event_GameLogicActivated("", -1));

	for (auto i : LogicsFactory::GetInstance()->m_factoryMap)
	{
		m_game_logic_names.emplace_back(i.first);
	}

	//for (auto g : GameLogicInstances)
	//{
	//	m_game_logic_names.emplace_back(g->GetName());
	//}
}

void GameLogicSystem::Uninitialize()
{

}

void GameLogicSystem::Update(SEfloat deltaTime)
{
	SE_Event se_event;

	while (m_event_handler->PollEvents(se_event))
	{
		switch (se_event.type)
		{
		case EventType::GameLogicActivated:
		{		
		//	auto index = m_engine.GetEntityMgr().GetEntities().at(se_event.additional_data.seint).components.at(COMPONENT_TYPE::GAMELOGIC);
		//	m_cGameLogic.at(index);
			auto spesificComponent = std::find_if(m_cGameLogic.begin(), m_cGameLogic.end(), _findByValue(se_event.additional_data.seint));

			if (spesificComponent != m_cGameLogic.end())
			{
				for (int i = 0; i < spesificComponent->logics.size(); ++i)
				{
					if (spesificComponent->logics.at(i)->GetName() == se_event.data.char_arr)
					{
						std::swap(spesificComponent->logics.at(0), spesificComponent->logics.at(i));
						std::cout << "swapped logics  : " << spesificComponent->logics.at(0)->GetName() << " - " 
							<< spesificComponent->logics.at(i)->GetName() << std::endl;
						break;
					}
				}
			}
			break;
		}
		default:
			break;
		}
	}

	for (auto& comp : m_cGameLogic)
	{
		if (comp.logics.size() != 0)
		{
			comp.logics.at(0)->Update(deltaTime); //Active set to 0
		}
	}
}

void GameLogicSystem::ClearComponentContainers()
{
	m_cGameLogic.clear();
}

void GameLogicSystem::OnEntityAdded(Entity& entity, Dataformat_itr& entity_obj)
{
	if (entity.components.count(COMPONENT_TYPE::GAMELOGIC))
	{
		SEint index = _onEntityAdded_helper(entity, COMPONENT_TYPE::GAMELOGIC, entity_obj, m_cGameLogic, m_free_cGameLogic_indices);
		auto& comp = m_cGameLogic.at(index);
		for (auto& name : comp.logic_class_names)
		{
			AssingGameLogic(name, comp);
		}
	}
}

void GameLogicSystem::OnEntityRemoved(Entity& entity)
{
	if (entity.components.count(COMPONENT_TYPE::GAMELOGIC))
	{
		m_free_cGameLogic_indices.push(entity.components.at(COMPONENT_TYPE::GAMELOGIC));
	}
}

SEint GameLogicSystem::CreateComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj)
{
	if (component_type == COMPONENT_TYPE::GAMELOGIC)
	{
		SEint index = _createComponent_helper<CGameLogic>(entity, component_type, entity_obj, m_cGameLogic, m_free_cGameLogic_indices);
		return index;
	}
	else
	{
		MessageWarning(GameLogicSys_id) << "Somehow tried to add component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return -1;
	}
}

void GameLogicSystem::RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj)
{
	if (component_type == COMPONENT_TYPE::GAMELOGIC)
	{
		m_free_cGameLogic_indices.push(_removeComponent_helper(entity, component_type, entity_obj, m_cGameLogic));
	}
	else
	{
		MessageWarning(GameLogicSys_id) << "Somehow tried to remove component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return;
	}
}

Component* GameLogicSystem::GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container)
{
	if (type == COMPONENT_TYPE::GAMELOGIC)
	{
		return &m_cGameLogic.at(index_in_container);
	}
	else
		return nullptr;
}

void GameLogicSystem::AssingGameLogic(std::string logic_name, CGameLogic& component)
{

	for (auto i : LogicsFactory::GetInstance()->m_factoryMap)
	{
		if (i.first == logic_name)
		{
			component.logics.emplace_back(LogicsFactory::GetInstance()->CreateLogic(logic_name));
			component.logics.back()->entityID(component.ownerID);
			return;
		}

	}
	MessageWarning(GameLogicSys_id) << "No GameLogic with name [" + logic_name + "] found\n in AssingGameLogic()";

	//	for (auto g : GameLogicInstances)
	//	{
	//		if (g->GetName() == logic_name)
	//		{
	//			component.logics.emplace_back(LogicsFactory::GetInstance()->CreateLogic(logic_name));
	//			component.logics.back()->entityID(component.ownerID);
	//			return;
	//		}
	//	}
	//	MessageWarning(GameLogicSys_id) << "No GameLogic with name [" + logic_name + "] found\n in AssingGameLogic()";
}

void GameLogicSystem::InitializeGameLogics()
{
	for (auto i : m_cGameLogic)
	{
		for (auto j : i.logics)
		{
			j->Init();
		}
	}
}

}//namespace priv
}//namespace se