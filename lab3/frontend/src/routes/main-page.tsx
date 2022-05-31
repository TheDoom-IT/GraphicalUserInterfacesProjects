import { useContext } from "react";
import { SessionContext, SessionContextType } from "../App";
import { WelcomePage } from "../components/WelcomePage";
import { WelcomeUserPage } from "../components/WelcomeUserPage";

export function MainPage() {
    const context: SessionContextType = useContext(SessionContext)

    return (
        <>
            {(context.isLoggedIn) ? (<WelcomeUserPage />) : (<WelcomePage />)}
        </>
    )
}