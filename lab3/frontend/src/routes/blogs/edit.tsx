import { StatusCodes } from "http-status-codes"
import { useContext, useEffect, useState } from "react"
import { useNavigate, useParams } from "react-router-dom"
import { SessionContext, SessionContextType } from "../../App"
import { Loading } from "../../components/Loading"
import { BASIC_HEADER, API_BLOGS_UPDATE, API_PRIVATE_BLOG_SHOW } from "../../constans"
import { getJWT } from "../../jwt-token"
import { PATH_BLOGS_SHOW_PARAM, PATH_FORBIDDEN } from "../constants"
import { ResponseBlogsShow, ResponseBlogsUpdate } from "../response-types"

export type BlogsEditParams = {
    id: string
}

export function BlogsEdit() {
    const context: SessionContextType = useContext(SessionContext)
    const { id } = useParams<BlogsEditParams>()

    const navigate = useNavigate()

    const [title, setTitle] = useState("")
    const [titleError, setTitleError] = useState("")
    const [isLoading, setIsLoading] = useState(true)

    const onSubmit = async (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault()

        const res = await fetch(API_BLOGS_UPDATE(Number(id)), {
            method: "PATCH",
            headers: getJWT(BASIC_HEADER),
            body: JSON.stringify({ title })
        })

        const response: ResponseBlogsUpdate = await res.json()

        if (res.status === StatusCodes.UNAUTHORIZED) {
            context.logOut()
            return
        }
        if (res.status === StatusCodes.BAD_REQUEST) {
            if (response.errors?.title)
                setTitleError(response.errors.title)
            return
        }

        if (res.status !== StatusCodes.OK) {
            navigate(PATH_FORBIDDEN)
            return
        }

        navigate(PATH_BLOGS_SHOW_PARAM(response.id))
    }

    useEffect(() => {
        if (context.isLoggedIn === false)
            navigate(PATH_FORBIDDEN)

        const loadBlog = async () => {
            const res = await fetch(API_PRIVATE_BLOG_SHOW(Number(id)), {
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
            const response: ResponseBlogsShow = await res.json()

            setTitle(response.title)
            setIsLoading(false)
        }

        loadBlog()
    }, [id, context, navigate])
    return (
        <div>
            {isLoading === true ? (<Loading />) :
                (<>
                    <h1>
                        Edit blog
                    </h1>
                    <form onSubmit={(e) => onSubmit(e)}>
                        <label className="myLabel">
                            Title:
                            <input className="textInput" id="title" value={title} required onChange={(e) => setTitle(e.currentTarget.value)} />
                            <div className='labelError'>{titleError}</div>
                        </label>
                        <div className="btn-group">
                            <input className="btn" type="submit" value="Save" />
                        </div>
                    </form>
                </>)}
        </div>

    )
}