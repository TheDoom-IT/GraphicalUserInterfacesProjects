import { StatusCodes } from "http-status-codes";
import { useContext, useEffect, useState } from "react";
import { Link, useNavigate } from "react-router-dom";
import { SessionContext, SessionContextType } from "../App";
import { BASIC_HEADER, API_CURRENT_USER } from "../constans";
import { getJWT } from "../jwt-token";
import { PATH_BLOGS_NEW, PATH_FORBIDDEN, PATH_USER_PROFILE } from "../routes/constants";
import { ResponseCurrentUser, User } from "../routes/response-types";
import { Loading } from "./Loading";

export function WelcomeUserPage() {
    const context: SessionContextType = useContext(SessionContext)
    const [isLoading, setIsLoading] = useState(true)
    const [user, setUser] = useState<User>()
    const navigate = useNavigate()

    useEffect(() => {
        const fetchCurrentUser = async () => {
            const res = await fetch(API_CURRENT_USER, {
                method: "GET",
                headers: getJWT(BASIC_HEADER)
            })

            if (res.status === StatusCodes.UNAUTHORIZED) {
                context.logOut()
                return
            }
            if (res.status !== StatusCodes.OK) {
                navigate(PATH_FORBIDDEN)
                return
            }

            const resUser: ResponseCurrentUser = await res.json()
            setUser(resUser)
            setIsLoading(false)
        }

        fetchCurrentUser()
    }, [context, navigate])
    return (
        <>
            {(isLoading) ? <Loading /> : (<>
                <h1>Welcome {user?.login}!</h1>
                <div className="text-center">
                    What do you want to do?
                </div>
                <div className="btn-group">
                    <Link className="btn" to={PATH_USER_PROFILE}>Browse your blogs</Link>
                    <Link className="btn" to={PATH_BLOGS_NEW}>Create new blog</Link>
                </div>
            </>)}
        </>
    )
}