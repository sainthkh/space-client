let styles = [%raw {| require("./Footer.scss") |}]

open Svgr;

module HomeSvgFile: Svg = { let component = req("../assets/home.svg") }
module CartSvgFile: Svg = { let component = req("../assets/cart.svg") }
module ProfileSvgFile: Svg = { let component = req("../assets/profile.svg") }

module HomeIcon = SvgComponent(HomeSvgFile);
module CartIcon = SvgComponent(CartSvgFile);
module ProfileIcon = SvgComponent(ProfileSvgFile);

let component = ReasonReact.statelessComponent("Footer")

let make = (_children) => {
  ...component,

  render: _self => {
    <footer className=styles##wrap>
      <div className=styles##menu>
        <Link href="/" className=styles##menuItem>
          <HomeIcon className=styles##icon />
          { ReasonReact.string("Home") }
        </Link>
        <Link href="/cart" className=styles##menuItem>
          <CartIcon className=styles##icon />
          { ReasonReact.string("Cart") }
        </Link>
        <Link href="/profile" className=styles##menuItem>
          <ProfileIcon className=styles##icon />
          { ReasonReact.string("Profile") }
        </Link>
      </div>
    </footer>
  }
}
