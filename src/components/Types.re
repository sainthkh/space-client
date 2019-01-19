type mission = {
  name: string,
  missionPatch: string,
}

type rocket = {
  id: int,
  name: string, 
  type_: string,
}

type launch = {
  id: int,
  site: string,
  backgroundImage: option(string),
  mission: mission,
  rocket: rocket,
  isBooked: bool,
}
