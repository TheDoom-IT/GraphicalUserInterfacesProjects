import { StatusCodes } from "http-status-codes"
import React, { useContext, useEffect, useState } from "react"
import { useNavigate, useParams } from "react-router-dom"
import { SessionContext, SessionContextType } from "../../App"
import { BASIC_HEADER, API_ENTRIES_CREATE } from "../../constans"
import { getJWT } from "../../jwt-token"
import { PATH_ENTRIES_SHOW_PARAM, PATH_FORBIDDEN } from "../constants"
import { ResponseEntriesCreate } from "../response-types"

export type EntriesNewParam = {
    blogId: string
}

export function EntriesNew() {
    const context: SessionContextType = useContext(SessionContext)
    const { blogId } = useParams<EntriesNewParam>()

    const navigate = useNavigate()

    const [title, setTitle] = useState("")
    const [content, setContent] = useState("")
    const [titleError, setTitleError] = useState("")
    const [contentError, setContentError] = useState("")

    const onSubmit = async (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault()

        const res = await fetch(API_ENTRIES_CREATE(Number(blogId)), {
            method: "POST",
            headers: getJWT(BASIC_HEADER),
            body: JSON.stringify({
                title,
                content
            })
        })

        const response: ResponseEntriesCreate = await res.json()
        switch (res.status) {
            case StatusCodes.UNAUTHORIZED: {
                context.logOut()
                return
            }
            case StatusCodes.CREATED: {
                navigate(PATH_ENTRIES_SHOW_PARAM(blogId!!, response.id))
                break
            }
            case StatusCodes.BAD_REQUEST: {
                if (response.errors?.title)
                    setTitleError(response.errors.title)
                if (response.errors?.content)
                    setContentError(response.errors.content)
                break
            }
            default: {
                navigate(PATH_FORBIDDEN)
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
                Create a new blog entry
            </h1>
            <form onSubmit={(e) => onSubmit(e)}>
                <label className="myLabel">
                    Title:
                    <input className="textInput" id="title" value={title} required onChange={(e) => setTitle(e.currentTarget.value)} />
                    <div className='labelError'>{titleError}</div>
                </label>
                <label className="myLabel">
                    Content:
                    <textarea className="textArea" id="content" value={content} required onChange={(e) => setContent(e.currentTarget.value)} />
                    <div className='labelError'>{contentError}</div>
                </label>
                <div className="btn-group">
                    <input className="btn" type="submit" value="Create" />
                </div>
            </form>
        </div>
    )
}