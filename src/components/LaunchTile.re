let styles = [%raw {| require("./LaunchTile.scss") |}]
let component = ReasonReact.statelessComponent("LaunchTile")

let background = backgroundImage => {
  switch(backgroundImage) {
  | None => ReactDOMRe.Style.make(~background="#bdbdbd", ())
  | Some(url) => ReactDOMRe.Style.make(~background={j|url("$url")|j}, ())
  }
};

let make = (
  ~launchId: int,
  ~missionName: string,
  ~rocketName: string,
  ~backgroundUrl: option(string),
  _children
) => {
  ...component,

  render: _self => {
    <Link 
      className=Cn.make([styles##wrap, "card"])
      href={j|/launch/$launchId|j} 
      style=background(backgroundUrl)
    >
      <h3>{ ReasonReact.string(missionName) }</h3>
      <h5>{ ReasonReact.string(rocketName) }</h5>
    </Link>
  }
}
