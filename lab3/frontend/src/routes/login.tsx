import { useContext, useEffect } from "react";
import { useNavigate } from "react-router-dom";
import { SessionContext, SessionContextType } from "../App";
import LoginForm from "../components/LoginForm";
import { PATH_FORBIDDEN } from "./constants";

export function Login() {
    const context: SessionContextType = useContext(SessionContext)
    const navigate = useNavigate()

    useEffect(() => {
        if (context.isLoggedIn)
            navigate(PATH_FORBIDDEN)

    }, [context.isLoggedIn, navigate])

    return (
        <LoginForm />
    )
}