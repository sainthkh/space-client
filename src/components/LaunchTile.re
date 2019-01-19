let styles = [%raw {| require("./LaunchTile.scss") |}]
let component = ReasonReact.statelessComponent("LaunchTile")

let make = (
  ~launch: Types.launch,
  _children
) => {
  ...component,

  render: _self => {
    let { id, mission, rocket }: Types.launch = launch;
    let background = backgroundImage => {
      switch(backgroundImage) {
      | None => ReactDOMRe.Style.make(~background="#bdbdbd", ())
      | Some(url) => ReactDOMRe.Style.make(~background={j|url("$url")|j}, ())
      }
    };

    <Link 
      className=styles##wrap href={j|/launch/$id|j} 
      style=background(launch.backgroundImage)
    >
      <h3>{ ReasonReact.string(mission.name) }</h3>
      <h5>{ ReasonReact.string(rocket.name) }</h5>
    </Link>
  }
}
