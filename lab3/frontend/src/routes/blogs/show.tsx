import { StatusCodes } from "http-status-codes"
import { useCallback, useContext, useEffect, useState } from "react"
import { Link, useNavigate, useParams } from "react-router-dom"
import { SessionContext, SessionContextType } from "../../App"
import { EntryItem } from "../../components/EntryItem"
import { Loading } from "../../components/Loading"
import { BASIC_HEADER, API_ENTRIES_DELETE, API_PRIVATE_BLOG_SHOW, API_ENTRIES } from "../../constans"
import { getJWT } from "../../jwt-token"
import { PATH_ENTIRES_NEW_PARAM, PATH_FORBIDDEN } from "../constants"
import { Blog, Entry, ResponseBlogsShow, ResponseEntriesIndex } from "../response-types"

export type BlogsShowParams = {
    id: string
}

export function BlogsShow() {
    const context: SessionContextType = useContext(SessionContext)
    const { id } = useParams<BlogsShowParams>()

    const navigate = useNavigate()
    const [blog, setBlog] = useState<Blog>()
    const [entries, setEntries] = useState<Entry[]>([])
    const [isLoadingBlog, setIsLoadingBlog] = useState(true)
    const [isLoadingEntries, setIsLoadingEntries] = useState(true)

    const onDeleteClick = async (entry: Entry) => {
        const result = window.confirm(`Are you sure you want to delete entry "${entry.title}"?`)
        if (!result)
            return

        const res = await fetch(API_ENTRIES_DELETE(entry.blogId, entry.id), {
            method: "DELETE",
            headers: getJWT(BASIC_HEADER)
        })

        // JWT token is invalid
        if (res.status === StatusCodes.UNAUTHORIZED) {
            context.logOut()
            return
        }
        if (res.status !== StatusCodes.NO_CONTENT) {
            navigate(PATH_FORBIDDEN)
            return
        }

        setIsLoadingEntries(true)
        fetchEntries()
    }

    useEffect(() => {
        if (context.isLoggedIn === false) {
            navigate(PATH_FORBIDDEN)
            return
        }
        if (isLoadingBlog === false)
            return
        const fetchBlog = async () => {
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

            const resBlog: ResponseBlogsShow = await res.json()
            setBlog(resBlog)
            setIsLoadingBlog(false)
        }
        fetchBlog()
    }, [context, id, navigate, isLoadingBlog])

    const fetchEntries = useCallback(async () => {
        const res = await fetch(API_ENTRIES(id!), {
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
        const resEntries: ResponseEntriesIndex = await res.json()
        setEntries(resEntries)
        setIsLoadingEntries(false)
    }, [context, id, navigate])

    useEffect(() => {
        if (!isLoadingBlog || !isLoadingEntries)
            fetchEntries()

    }, [isLoadingBlog, id, context, navigate, fetchEntries, isLoadingEntries])

    return (
        <div>
            {isLoadingBlog === true || isLoadingEntries === true ? (<Loading />) : (
                <>
                    <h1>{blog?.title}</h1>
                    <div className="page-options">
                        <Link className="btn" to={PATH_ENTIRES_NEW_PARAM(Number(id))}>New entry</Link>
                    </div>
                    <div className="card-list">
                        {entries.map(entry => <EntryItem key={entry.id} entry={entry} onDeleteClick={onDeleteClick} />)}
                    </div>
                </>
            )
            }
        </div >
    )
}