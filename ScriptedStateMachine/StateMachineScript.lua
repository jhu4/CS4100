-------------------------------------------------------------------------------

-- create the Global state

-------------------------------------------------------------------------------
State_Global={}

State_Global["Enter"] = function(miner)
  --nothing  
end 

State_Global["Execute"] = function(miner)

  if not miner:IsPeein() then 
    print ("[Lua]:(fill bladder) "..miner:getBladderVal())
    miner:FillBladder(1)
  end 

  if miner:IsBladderFull() then
    miner:GetFSM():ChangeState(State_Pee)
  end

end 

State_Global["Exit"] = function(miner)
  --nothing
end

-------------------------------------------------------------------------------

-- create the Pee state

-------------------------------------------------------------------------------
State_Pee={}

State_Pee["Enter"] = function(miner)
  print ("[Lua]: Walkin to the bathroom")
end

State_Pee["Execute"] = function(miner)
  print ('[Lua]: Peein')
  miner:EmptyBladder()
  miner:GetFSM():RevertToPreviousState()
end

State_Pee["Exit"] = function(miner)
  print ('[Lua]: Leavin the bathroom')
end

-------------------------------------------------------------------------------

-- create the GoHome state

-------------------------------------------------------------------------------
State_GoHome = {}


State_GoHome["Enter"] = function(miner)

  print ("[Lua]: Walkin home in the hot n' thusty heat of the desert")

end


State_GoHome["Execute"] = function(miner)

  print ("[Lua]: Back at the shack. yer siree!")

  if miner:Fatigued() then

    miner:GetFSM():ChangeState(State_Sleep)

  else

    miner:GetFSM():ChangeState(State_GoToMine)

  end

end

  
State_GoHome["Exit"] = function(miner)

  print ("[Lua]: Puttin' mah boots on n' gettin' ready for a day at the mine")

end



-------------------------------------------------------------------------------

-- create the Sleep state

-------------------------------------------------------------------------------

State_Sleep = {}


State_Sleep["Enter"] = function(miner)

  print ("[Lua]: Miner "..miner:Name().." is dozin off")

end


State_Sleep["Execute"] = function(miner)

  if miner:Fatigued() then

    print ("[Lua]: ZZZZZZ... ")

    miner:DecreaseFatigue()

  else

    miner:GetFSM():ChangeState(State_GoToMine)

  end

end

State_Sleep["Exit"] = function(miner)

  print ("[Lua]: Miner "..miner:Name().." is feelin' mighty refreshed!")

end


-------------------------------------------------------------------------------

-- create the GoToMine state

-------------------------------------------------------------------------------


State_GoToMine = {}


State_GoToMine["Enter"] = function(miner)

  print ("[Lua]: Miner "..miner:Name().." enters goldmine")

end


State_GoToMine["Execute"] = function(miner)

  miner:IncreaseFatigue()

  miner:AddToGoldCarried(2)

  print ("[Lua]: Miner "..miner:Name().." has got "..miner:GoldCarried().." nuggets")


  if miner:GoldCarried() > 4 then
  
    print ("[Lua]: Miner "..miner:Name().." decides to go home, with his pockets full of nuggets")

    miner:GetFSM():ChangeState(State_GoHome)

  end

end


State_GoToMine["Exit"] = function(miner)

  print ("[Lua]: Miner "..miner:Name().." exits goldmine")

  end




 