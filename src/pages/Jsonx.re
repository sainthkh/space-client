open Js;
open Js.Dict;
open Belt.Option;

let obj = json => 
  Json.decodeObject(json)
  ->mapWithDefault(Dict.empty(), dict => dict);

let array = ar =>
  Json.decodeArray(ar)
  ->mapWithDefault([||], a => a);

let string = str =>
  Json.decodeString(str)
  ->mapWithDefault("", s => s);

let boolean = boolean => 
  Json.decodeBoolean(boolean)
  ->mapWithDefault(false, b => b)

let defaultIfNone = (dict, key, default) => 
  dict->get(key)
  ->mapWithDefault(default, v => v);

let defaultBooleanIfNone = (dict, key, default) => 
  defaultIfNone(dict, key, Js.Json.boolean(default))->boolean

let emptyIfNone = (dict, key) => {
  let json = dict->Dict.get(key)
  switch(json) {
  | None => Dict.empty()
  | Some(json) => obj(json)
  }
}

let concat = (a1, a2) => {
  let a1 = array(a1)
  let a2 = array(a2)
  Array.concat(a1, a2)
  ->Json.array
}