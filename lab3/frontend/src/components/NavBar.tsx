import { useContext } from "react";
import { Link } from "react-router-dom";
import { SessionContext, SessionContextType } from "../App";
import { PATH_LOGIN, PATH_REGISTER, PATH_USER_PROFILE } from "../routes/constants";

export function NavBar() {
    const context: SessionContextType = useContext(SessionContext)

    return (
        <nav className="navbar">
            <div className="navitem">
                <Link to={"/"}>Home</Link>
            </div>
            {context.isLoggedIn === false &&
                <>
                    <div className="navbar-rigth">
                        <div className="navitem">
                            <Link to={PATH_LOGIN}>Login</Link>
                        </div>
                        <div className="navitem">
                            <Link to={PATH_REGISTER}>Register</Link>
                        </div>
                    </div>
                </>
            }
            {context.isLoggedIn === true &&
                <>
                    <div className="navitem">
                        <Link to={PATH_USER_PROFILE}>Profile</Link>
                    </div>
                    <div className="navbar-rigth">
                        <div className="navitem">
                            < Link to={"/"} onClick={context.logOut}>Log out</Link>
                        </div>
                    </div>
                </>
            }
        </nav >
    )
}