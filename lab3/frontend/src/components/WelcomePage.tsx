import { Link } from "react-router-dom";
import { PATH_LOGIN, PATH_REGISTER } from "../routes/constants";

export function WelcomePage() {
    return (
        <>
            <h1>Welcome to Blo.gg!</h1>
            <div className="text-center">
                Create or use an existing account to start writing amazing blogs!
            </div>
            <div className="btn-group">
                <Link className="btn" to={PATH_LOGIN}>Sign In</Link>
                <Link className="btn" to={PATH_REGISTER}>Sign Up</Link>
            </div>
        </>
    )
}