import { StatusCodes } from "http-status-codes"
import { useContext, useEffect, useState } from "react"
import { Link, useNavigate, useParams } from "react-router-dom"
import { SessionContext, SessionContextType } from "../../App"
import { Loading } from "../../components/Loading"
import { BASIC_HEADER, API_ENTRIES_DELETE, API_PRIVATE_BLOG_ENTRIES_SHOW } from "../../constans"
import { getJWT } from "../../jwt-token"
import { PATH_BLOGS_SHOW_PARAM, PATH_ENTRIES_EDIT_PARAM, PATH_FORBIDDEN } from "../constants"
import { Entry, ResponseEntriesShow } from "../response-types"

export type EntriesShowParam = {
    id: string
    blogId: string
}

export function EntriesShow() {
    const context: SessionContextType = useContext(SessionContext)
    const { id, blogId } = useParams<EntriesShowParam>()

    const navigate = useNavigate()
    const [entry, setEntry] = useState<Entry>()
    const [isLoading, setIsLoading] = useState(true)

    const onDeleteClick = async () => {
        const result = window.confirm(`Are you sure you want to delete entry "${entry?.title}"?`)
        if (!result)
            return

        const res = await fetch(API_ENTRIES_DELETE(entry?.blogId!!, entry?.id!!), {
            method: "DELETE",
            headers: getJWT(BASIC_HEADER)
        })

        if (res.status === StatusCodes.UNAUTHORIZED) {
            context.logOut()
            return
        } else if (res.status !== StatusCodes.NO_CONTENT) {
            navigate(PATH_FORBIDDEN)
            return
        }

        navigate(PATH_BLOGS_SHOW_PARAM(entry?.blogId!!))
    }

    useEffect(() => {
        if (context.isLoggedIn === false) {
            navigate(PATH_FORBIDDEN)
            return
        }
        const fetchEntry = async () => {
            const res = await fetch(API_PRIVATE_BLOG_ENTRIES_SHOW(blogId!!, id!!), {
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

            const resEntry: ResponseEntriesShow = await res.json()
            setEntry(resEntry)
            setIsLoading(false)
        }

        fetchEntry()
    }, [blogId, id, navigate, context])

    return (
        <div>
            {isLoading === true ? (<Loading />) : (
                <>
                    <h1>{entry?.title}</h1>
                    <div className="page-options">
                        <Link className="btn" to={PATH_ENTRIES_EDIT_PARAM(entry?.blogId!!, entry?.id!!)}>Edit</Link>
                        <button className="btn btn-red" onClick={onDeleteClick}>Delete</button>
                    </div>
                    <div>
                        <Link className="btn" to={PATH_BLOGS_SHOW_PARAM(entry?.blogId!!)} >&crarr;Return to blog</Link>
                    </div>
                    <div className="entry-datetime">
                        {(new Date(entry?.datetime!!)).toLocaleDateString()}
                    </div>
                    <div className="entry-content">
                        {entry?.content}
                    </div>
                </>
            )}
        </div>
    )
}