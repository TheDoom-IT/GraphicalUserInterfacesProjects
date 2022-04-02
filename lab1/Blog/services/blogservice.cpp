#include "blogservice.h"

BlogService::BlogService(BlogRepository* blogRepository)
{
    this->blogRepository = blogRepository;
    this->currentBlog = nullptr;
}

std::pair<bool, QString> BlogService::createEmptyBlog(QString title, QString userId)
{
    auto blog = blogRepository->findOne(title);
    // blog with given title already exists
    if(blog.has_value())
        return std::pair(false, tr("Blog with such a title already exists."));

    if(this->currentBlog != nullptr)
        delete this->currentBlog;

    this->currentBlog = new Blog(title, userId,QList<BlogEntry>());
    std::pair<bool, QString> result = this->blogRepository->insertOne(*this->currentBlog);
    if(!result.first)
        return result;


    return std::pair(true, "");
}

bool BlogService::loadBlogOfUser(QString userId)
{
    auto blog = this->blogRepository->findOneByOwner(userId);
    if(blog.has_value())
    {
        this->currentBlog = new Blog(blog.value());
        return true;
    }

    this->currentBlog = nullptr;
    return false;
}

void BlogService::removeEntries(QList<int> indices)
{
    for(int index : indices)
    {
        currentBlog->removeEntry(index);
    }

    blogRepository->updateOne(*currentBlog);
}

std::pair<bool, QString> BlogService::updateEntry(int index, QString title, QString content)
{
    currentBlog->updateEntry(index, title, content);
    auto result = blogRepository->updateOne(*currentBlog);
    if(!result.first)
        return result;

    return std::pair(true, "");
}

std::pair<bool, QString> BlogService::addEntry(QString title, QString content)
{
    BlogEntry blogEntry(title, QDateTime::currentDateTime(), content);
    currentBlog->addEntry(blogEntry);
    auto result = blogRepository->updateOne(*currentBlog);
    if(!result.first)
        return result;

    return std::pair(true, "");
}
