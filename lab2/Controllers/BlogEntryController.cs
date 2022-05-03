using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using blog.Models;
using blog.Context;
using blog.Services;
using blog.Controllers;

namespace blog
{
    public class BlogEntryController : BaseController
    {

        public BlogEntryController(ILogger<LoginController> logger, IDbContextFactory<BlogContext> blogContextFactory, IUserService userService)
        : base(logger, blogContextFactory, userService)
        {
        }

        public IActionResult Show(int BlogId, int Id)
        {
            if (CurrentUser == null)
                return this.RedirectToAction("Index", "Login");

            using (var db = _blogContextFactory.CreateDbContext())
            {
                var blog = db.Blogs.Where(e => e.Id == BlogId && e.UserId == CurrentUserId).FirstOrDefault();
                var entry = db.BlogEntries.Where(e => e.Id == Id && e.UserId == CurrentUserId).FirstOrDefault();
                if (entry == null || blog == null || entry.BlogId != BlogId)
                {
                    return this.RedirectToAction("Forbidden", "Home");
                }

                return View(entry);
            }
        }

        [HttpPost]
        public IActionResult Delete(int BlogId, int Id)
        {
            if (CurrentUser == null)
                return this.RedirectToAction("Index", "Login");

            using (var db = _blogContextFactory.CreateDbContext())
            {
                var blog = db.Blogs.Where(e => e.Id == BlogId && e.UserId == CurrentUserId).FirstOrDefault();
                var entry = db.BlogEntries.Where(e => e.Id == Id && e.UserId == CurrentUserId).FirstOrDefault();

                if (entry == null || blog == null || entry.BlogId != BlogId)
                {
                    return this.RedirectToAction("Forbidden", "Home");

                }

                db.BlogEntries.Remove(entry);
                db.SaveChanges();

                return this.RedirectToAction("Show", "Blog", new { Id = entry.BlogId });
            }
        }

        public IActionResult Edit(int BlogId, int Id)
        {
            if (CurrentUser == null)
                return this.RedirectToAction("Index", "Login");

            using (var db = _blogContextFactory.CreateDbContext())
            {
                var blog = db.Blogs.Where(e => e.Id == BlogId && e.UserId == CurrentUserId).FirstOrDefault();
                var entry = db.BlogEntries.Where(e => e.Id == Id && e.UserId == CurrentUserId).FirstOrDefault();

                if (entry == null || blog == null || entry.BlogId != BlogId)
                {
                    return this.RedirectToAction("Forbidden", "Home");
                }

                return View(entry);
            }
        }

        [HttpPost]
        public IActionResult Edit(int BlogId, BlogEntry editEntry)
        {
            _logger.LogDebug($"EditBlogEntry: BlogId {BlogId} entryId: {editEntry.Id} new title: {editEntry.Title}");
            if (CurrentUser == null)
                return this.RedirectToAction("Index", "Login");

            using (var db = _blogContextFactory.CreateDbContext())
            {
                var blog = db.Blogs.Where(e => e.Id == BlogId && e.UserId == CurrentUserId).FirstOrDefault();
                var entry = db.BlogEntries.Where(e => e.Id == editEntry.Id && e.UserId == CurrentUserId).FirstOrDefault();

                if (entry == null || blog == null || entry.BlogId != BlogId)
                {
                    return this.RedirectToAction("Forbidden", "Home");
                }

                entry.Title = editEntry.Title;
                entry.Content = editEntry.Content;
                entry.UserId = CurrentUser!.Id;
                db.BlogEntries.Update(entry);

                db.SaveChanges();

                return this.RedirectToAction("Show", "BlogEntry", new { BlogId = BlogId, Id = editEntry.Id });
            }
        }

        public IActionResult New(int BlogId)
        {
            if (CurrentUser == null)
                return this.RedirectToAction("Index", "Login");

            using (var db = _blogContextFactory.CreateDbContext())
            {
                var blog = db.Blogs.Where(e => e.Id == BlogId && e.UserId == CurrentUserId).FirstOrDefault();
                if (blog == null)
                    return this.RedirectToAction("Forbidden", "Home");
            }

            var blogEntry = new BlogEntry() { BlogId = BlogId };
            return View(blogEntry);
        }

        [HttpPost]
        public IActionResult Create(int BlogId, BlogEntry entry)
        {
            _logger.LogInformation($"CreateBlogEntry: BlogId {BlogId} Title: {entry.Title}, Content: {entry.Content}");
            if (CurrentUser == null)
                return this.RedirectToAction("Index", "Login");

            using (var db = _blogContextFactory.CreateDbContext())
            {
                var blog = db.Blogs.Where(e => e.Id == BlogId && e.UserId == CurrentUserId).FirstOrDefault();
                if (blog == null)
                    return this.RedirectToAction("Forbidden", "Home");

                entry.UserId = CurrentUser!.Id;
                entry.DateTime = DateTime.Now;
                entry.BlogId = BlogId;
                db.BlogEntries.Add(entry);
                db.SaveChanges();

                return this.RedirectToAction("Show", "BlogEntry", new { BlogId = BlogId, Id = entry.Id });
            }
        }
    }
}