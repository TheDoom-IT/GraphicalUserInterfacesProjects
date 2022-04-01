#include "blogservice.h"
#include <QtDebug>

BlogService::BlogService(BlogRepository* blogRepository)
{
    this->blogRepository = blogRepository;
    this->currentBlog = nullptr;
}

std::pair<bool, QString> BlogService::createEmptyBlog(QString title, QString userId)
{
    auto blog = blogRepository->findOne(title);
    if(blog.has_value())
        return std::pair(false, tr("Blog with such a title already exists."));

    // create new blog
    if(this->currentBlog == nullptr)
    {
        delete this->currentBlog;
    }

    this->currentBlog = new Blog(title, userId,QList<BlogEntry>());
    this->blogRepository->insertOne(*this->currentBlog);

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

void BlogService::updateEntry(int index, QString title, QString content)
{
    currentBlog->updateEntry(index, title, content);
    blogRepository->updateOne(*currentBlog);
}

void BlogService::addEntry(QString title, QString content)
{
    BlogEntry blogEntry(title, QDateTime::currentDateTime(), content);
    currentBlog->addEntry(blogEntry);
    blogRepository->updateOne(*currentBlog);
}
