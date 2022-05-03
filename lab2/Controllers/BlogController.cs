using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using blog.Models;
using blog.Context;
using blog.Services;
using blog.Controllers;

namespace blog
{
    public class BlogController : BaseController
    {

        public BlogController(ILogger<LoginController> logger, IDbContextFactory<BlogContext> blogContextFactory, IUserService userService)
        : base(logger, blogContextFactory, userService)
        {
        }

        public IActionResult Show(int Id)
        {
            if (CurrentUser == null)
                return this.RedirectToAction("Index", "Login");

            using (var db = _blogContextFactory.CreateDbContext())
            {
                var blog = db.Blogs.Where(b => b.Id == Id && b.UserId == CurrentUserId).FirstOrDefault();
                if (blog == null)
                {
                    return this.RedirectToAction("Forbidden", "Home");
                }

                var entries = db.BlogEntries.Where(e => e.BlogId == blog.Id).OrderByDescending(e => e.DateTime).ToList();
                blog.BlogEntries = entries;

                return View(blog);
            }
        }

        [HttpPost]
        public IActionResult Delete(int Id)
        {
            if (CurrentUser == null)
                return this.RedirectToAction("Index", "Login");

            using (var db = _blogContextFactory.CreateDbContext())
            {
                var blog = db.Blogs.Where(b => b.Id == Id && b.UserId == CurrentUserId).FirstOrDefault();

                if (blog == null)
                {
                    return this.RedirectToAction("Forbidden", "Home");

                }

                db.Blogs.Remove(blog);
                var entries = db.BlogEntries.Where(e => e.BlogId == Id);
                db.RemoveRange(entries);
                db.SaveChanges();
            }
            return this.RedirectToAction("Index", "UserPanel");
        }

        public IActionResult Edit(int Id)
        {
            if (CurrentUser == null)
                return this.RedirectToAction("Index", "Login");

            using (var db = _blogContextFactory.CreateDbContext())
            {
                var blog = db.Blogs.Where(b => b.Id == Id && b.UserId == CurrentUserId).FirstOrDefault();

                if (blog == null)
                {
                    return this.RedirectToAction("Forbidden", "Home");
                }

                return View(blog);
            }
        }

        [HttpPost]
        public IActionResult Edit(Blog editBlog)
        {
            if (CurrentUser == null)
                return this.RedirectToAction("Index", "Login");

            using (var db = _blogContextFactory.CreateDbContext())
            {
                var blog = db.Blogs.Where(b => b.Id == editBlog.Id && b.UserId == CurrentUserId).FirstOrDefault();

                if (blog == null)
                {
                    return this.RedirectToAction("Forbidden", "Home");
                }

                // check if title is unique
                if (db.Blogs.Where(b => b.Id != editBlog.Id && b.Title == editBlog.Title).Count() > 0)
                {
                    TempData["Error"] = "Blog with a given title already exists";
                    return this.RedirectToAction("Edit");
                }

                blog.Title = editBlog.Title;
                db.Blogs.Update(blog);

                db.SaveChanges();

                return this.RedirectToAction("Show", "Blog", new { @Id = blog.Id });
            }
        }

        public IActionResult New()
        {
            if (CurrentUser == null)
                return this.RedirectToAction("Index", "Login");

            return View();
        }

        [HttpPost]
        public IActionResult Create(Blog blog)
        {
            if (CurrentUser == null)
                return this.RedirectToAction("Index", "Login");

            using (var db = _blogContextFactory.CreateDbContext())
            {
                if (db.Blogs.Where(b => b.Title == blog.Title).Count() > 0)
                {
                    TempData["Error"] = "Blog with a given title already exists";
                    return this.RedirectToAction("New");
                }

                blog.UserId = CurrentUser!.Id;
                db.Blogs.Add(blog);
                db.SaveChanges();
            }

            return this.RedirectToAction("Show", "Blog", new { Id = blog.Id });
        }
    }
}