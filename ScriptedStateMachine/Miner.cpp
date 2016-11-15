#include "Miner.h"


Miner::Miner(std::string    name):m_iGoldCarried(0),
                                  m_iFatigue(0),
                                  m_iBladder(0),
                                  m_iPeein(false),
                                  Entity(name)
                               
{
  m_pStateMachine = new ScriptedStateMachine<Miner>(this);
}

void Miner::AddToGoldCarried(int val)
{
  m_iGoldCarried += val;

  if (m_iGoldCarried < 0) m_iGoldCarried = 0;
}


void Miner::Update()
{
  m_pStateMachine->Update(); 
}

bool Miner::Fatigued()const
{
  if (m_iFatigue > TirednessThreshold)
  {
    return true;
  }

  return false;
}

//*If the baddler of the miner is full
bool Miner::IsBladderFull(){
  if(m_iBladder>=BladderThreshold){
    m_iPeein=true;
    return true;
  }

  return false;
}

void Miner::EmptyBladder(){
  m_iBladder=0;
  m_iPeein=false;
}