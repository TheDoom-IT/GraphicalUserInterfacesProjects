using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using blog.Models;
using blog.Context;
using blog.Services;
using blog.Controllers;

namespace blog
{
    public class LoginController : BaseController
    {
        private readonly ILoginService _loginService;


        public LoginController(ILogger<LoginController> logger, IDbContextFactory<BlogContext> blogContextFactory, ILoginService loginService, IUserService userService)
        : base(logger, blogContextFactory, userService)
        {
            _loginService = loginService;
        }

        public IActionResult Index()
        {
            if (CurrentUser != null)
            {
                return this.RedirectToAction("Index", "Home");
            }
            return View();
        }

        public IActionResult Register()
        {
            if (CurrentUser != null)
            {
                return this.RedirectToAction("Index", "Home");
            }

            return View();
        }

        [HttpPost]
        public IActionResult CreateUser(User user)
        {
            if (CurrentUser != null)
            {
                return this.RedirectToAction("Index", "Home");
            }

            try
            {
                _loginService.Register(user);
            }
            catch (Exception e)
            {
                if (e is InvalidLoginException || e is InvalidEmailException)
                {
                    TempData["Error"] = e.Message;
                    return this.RedirectToAction("Register");
                }
                throw;
            }

            TempData["Information"] = "Account succesfully created. You can now sign in.";
            return this.RedirectToAction("Index");
        }

        [HttpPost]
        public IActionResult LogIn(User user)
        {
            if (CurrentUser != null)
            {
                return this.RedirectToAction("Index", "Home");
            }

            if (!_loginService.LogIn(user))
            {
                TempData["Error"] = "Invalid login and/or password";
                return this.RedirectToAction("Index");
            }

            return this.RedirectToAction("Index", "Home");
        }

        public IActionResult LogOut()
        {
            _loginService.LogOut();
            return this.RedirectToAction("Index", "Home");
        }
    }
}