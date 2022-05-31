import { StatusCodes } from "http-status-codes"
import { useContext, useEffect, useState } from "react"
import { useNavigate, useParams } from "react-router-dom"
import { SessionContext, SessionContextType } from "../../App"
import { Loading } from "../../components/Loading"
import { BASIC_HEADER, API_ENTRIES_UPDATE, API_PRIVATE_BLOG_ENTRIES_SHOW } from "../../constans"
import { getJWT } from "../../jwt-token"
import { PATH_ENTRIES_SHOW_PARAM, PATH_FORBIDDEN } from "../constants"
import { ResponseEntriesShow, ResponseEntriesUpdate } from "../response-types"

export type EntriesEditParam = {
    id: string
    blogId: string
}

export function EntriesEdit() {
    const context: SessionContextType = useContext(SessionContext)

    const { id, blogId } = useParams<EntriesEditParam>()

    const navigate = useNavigate()

    const [title, setTitle] = useState("")
    const [content, setContent] = useState("")
    const [titleError, setTitleError] = useState("")
    const [contentError, setContentError] = useState("")
    const [isLoading, setIsLoading] = useState(true)


    useEffect(() => {
        if (context.isLoggedIn === false) {
            navigate(PATH_FORBIDDEN)
            return
        }

        const fetchEntry = async () => {
            const res = await fetch(API_PRIVATE_BLOG_ENTRIES_SHOW(Number(blogId), Number(id)), {
                method: "GET",
                headers: getJWT(BASIC_HEADER)
            })

            if (res.status === StatusCodes.UNAUTHORIZED) {
                context.logOut()
                return
            } else if (res.status !== StatusCodes.OK) {
                navigate(PATH_FORBIDDEN)
                return
            }

            const entry: ResponseEntriesShow = await res.json()
            setTitle(entry.title)
            setContent(entry.content)
            setIsLoading(false)
        }
        fetchEntry()
    }, [context, navigate, blogId, id])

    const onSubmit = async (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault()
        const res = await fetch(API_ENTRIES_UPDATE(Number(blogId), Number(id)), {
            method: "PATCH",
            headers: getJWT(BASIC_HEADER),
            body: JSON.stringify({ title, content })
        })

        const response: ResponseEntriesUpdate = await res.json()
        if (res.status === StatusCodes.BAD_REQUEST) {
            if (response.errors?.title)
                setTitleError(response.errors.title)
            if (response.errors?.content)
                setContentError(response.errors.content)
            return
        }

        if (res.status !== StatusCodes.OK) {
            navigate(PATH_FORBIDDEN)
            return
        }

        navigate(PATH_ENTRIES_SHOW_PARAM(Number(blogId), response.id))
    }
    return (
        <div>
            {isLoading === true ? (<Loading />) :
                (<>
                    <h1>Edit entry</h1>
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
                            <input className="btn" type="submit" value="Save" />
                        </div>
                    </form>
                </>)}
        </div>

    )
}