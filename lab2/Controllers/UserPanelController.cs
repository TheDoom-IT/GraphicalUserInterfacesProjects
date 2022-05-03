using Microsoft.AspNetCore.Mvc;
using blog.Context;
using blog.Services;
using blog.Models;
using Microsoft.EntityFrameworkCore;

namespace blog.Controllers;

public class UserPanelController : BaseController
{
    public UserPanelController(ILogger<HomeController> logger, IDbContextFactory<BlogContext> blogContextFactory, IUserService userService) : base(logger, blogContextFactory, userService)
    {
    }

    public IActionResult Index()
    {
        // Only Logged user can access this page
        if (!_userService.IsLoggedIn())
            return this.RedirectToAction("Index", "Login");

        var data = new UserPanelViewModel();
        using (var db = _blogContextFactory.CreateDbContext())
        {
            data.Blogs = db.Blogs.Where(b => b.UserId == _userService.CurrentUser()!.Id).ToList();
        }
        return View(data);
    }
}
