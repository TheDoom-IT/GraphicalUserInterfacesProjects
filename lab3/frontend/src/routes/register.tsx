import { useContext, useEffect } from "react";
import { useNavigate } from "react-router-dom";
import { SessionContext, SessionContextType } from "../App";
import RegisterForm from "../components/RegisterForm";
import { PATH_FORBIDDEN } from "./constants";

export function Register() {
    const context: SessionContextType = useContext(SessionContext)
    const navigate = useNavigate()

    useEffect(() => {
        if (context.isLoggedIn)
            navigate(PATH_FORBIDDEN)

    }, [context.isLoggedIn, navigate])

    return (
        <RegisterForm />
    )
}