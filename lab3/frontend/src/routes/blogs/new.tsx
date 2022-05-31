import { StatusCodes } from "http-status-codes"
import React, { useContext, useEffect, useState } from "react"
import { useNavigate } from "react-router-dom"
import { SessionContext, SessionContextType } from "../../App"
import { BASIC_HEADER, API_BLOGS_CREATE } from "../../constans"
import { getJWT } from "../../jwt-token"
import { PATH_BLOGS_SHOW_PARAM, PATH_FORBIDDEN } from "../constants"
import { ResponseBlogsCreate } from "../response-types"

export function BlogsNew() {
    const context: SessionContextType = useContext(SessionContext)
    const navigate = useNavigate()
    const [title, setTitle] = useState("")
    const [titleError, setTitleError] = useState("")

    const onSubmit = async (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault()

        const res = await fetch(API_BLOGS_CREATE, {
            method: "POST",
            headers: getJWT(BASIC_HEADER),
            body: JSON.stringify({
                title
            })
        })

        const response: ResponseBlogsCreate = await res.json()

        switch (res.status) {
            case StatusCodes.UNAUTHORIZED: {
                context.logOut()
                return
            }
            case StatusCodes.BAD_REQUEST: {
                if (response.errors?.title)
                    setTitleError(response.errors.title)

                break
            }
            case StatusCodes.CREATED: {
                navigate(PATH_BLOGS_SHOW_PARAM(response.id!))
                break;
            }
            default: {
                navigate(PATH_FORBIDDEN)
                return
            }
        }
    }

    useEffect(() => {
        if (context.isLoggedIn === false)
            navigate(PATH_FORBIDDEN)
    }, [context, navigate])

    return (
        <div>
            <h1>
                Create a new blog
            </h1>
            <form onSubmit={(e) => onSubmit(e)}>
                <label className="myLabel">
                    Title:
                    <input className="textInput" id="title" value={title} required onChange={(e) => setTitle(e.currentTarget.value)} />
                    <div className='labelError'>{titleError}</div>
                </label>
                <div className="btn-group">
                    <input className="btn" type="submit" value="Create" />
                </div>
            </form>
        </div>
    )
}