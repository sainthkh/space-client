let styles = [%raw {| require("./Loading.scss") |}]
let component = ReasonReact.statelessComponent("Loading");

open Svgr;

module SvgFile: Svg = {
  let component = req("../assets/loading.svg")
}

module SVG = SvgComponent(SvgFile);

let make = (_children) => {
  ...component,

  render: _self => {
    <SVG 
      className=styles##wrap
      style=ReactDOMRe.Style.make(~width="100", ())
    />
  }
};


