let styles = [%raw {| require("./LaunchTile.scss") |}]
let component = ReasonReact.statelessComponent("LaunchTile")

let make = (
  ~launchID: int,
  ~missionName: string,
  ~rocketName: string,
  ~backgroundUrl: option(string),
  _children
) => {
  ...component,

  render: _self => {
    let background = backgroundImage => {
      switch(backgroundImage) {
      | None => ReactDOMRe.Style.make(~background="#bdbdbd", ())
      | Some(url) => ReactDOMRe.Style.make(~background={j|url("$url")|j}, ())
      }
    };

    <Link 
      className=styles##wrap href={j|/launch/$launchID|j} 
      style=background(backgroundUrl)
    >
      <h3>{ ReasonReact.string(missionName) }</h3>
      <h5>{ ReasonReact.string(rocketName) }</h5>
    </Link>
  }
}
