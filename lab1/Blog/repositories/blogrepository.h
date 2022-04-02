#ifndef BLOGREPOSITORY_H
#define BLOGREPOSITORY_H

#include <QString>
#include <QCoreApplication>
#include <QDir>
#include <optional>
#include "../models/blog.h"

class BlogRepository
{
    Q_DECLARE_TR_FUNCTIONS(LoginService)

    static const QString OWNER_ID_INDEX;
public:
    BlogRepository(QString dataPath, QString blogsDir);
    ~BlogRepository();

    std::optional<Blog> findOneByOwner(QString ownerId) const;
    std::optional<Blog> findOne(QString blogId) const;
    std::pair<bool, QString> insertOne(const Blog&) const;
    std::pair<bool, QString> updateOne(const Blog&) const;

private:
    QDir dataDir;
    QDir indexDir;

    bool prepareIndexDir(QString dataPath, QString blogsDir);
    bool prepareDataDir(QString dataPath, QString blogsDir);

    std::pair<bool, QString> writeBlogFile(const Blog&) const;
    std::pair<bool, QString> writeOwnerIdIndexFile(const Blog&) const;

    void throwUnableToAccessData() const;
};

#endif // BLOGREPOSITORY_H
