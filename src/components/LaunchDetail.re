let styles = [%raw {| require("./LaunchDetail.scss") |}]
let component = ReasonReact.statelessComponent("LaunchDetail")

let make = (
  ~rocketName: string,
  ~rocketType: string,
  ~site: string,
  ~backgroundUrl: option(string),
  _children
) => {
  ...component,

  render: _self => {
    <div 
      className=styles##wrap 
      style=LaunchTile.background(backgroundUrl)>
      <h3>{ ReasonReact.string({j|$rocketName ($rocketType)|j}) }</h3>
      <h5>{ ReasonReact.string(site) }</h5>
    </div>
  }
}
