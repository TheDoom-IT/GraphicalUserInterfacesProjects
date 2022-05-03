using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using blog.Models;
using blog.Context;
using blog.Services;
using Microsoft.EntityFrameworkCore;

namespace blog.Controllers;

public class HomeController : BaseController
{
    public HomeController(ILogger<HomeController> logger, IDbContextFactory<BlogContext> blogContextFactory, IUserService userService) : base(logger, blogContextFactory, userService)
    {
    }

    public IActionResult Index()
    {
        return View();
    }

    public IActionResult Forbidden()
    {
        return View();
    }
}