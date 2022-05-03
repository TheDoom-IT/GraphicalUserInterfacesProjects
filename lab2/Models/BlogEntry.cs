namespace blog.Models;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

public class BlogEntry
{
    const int TITLE_MIN_LENGTH = 5;
    const int TITLE_MAX_LENGTH = 200;
    const int CONTENT_MIN_LENGTH = 5;

    [Key]
    public int Id { get; set; }

    [Required(ErrorMessage = "The field is required")]
    [MinLength(TITLE_MIN_LENGTH, ErrorMessage = "Title should be at least 5 characters long")]
    [MaxLength(TITLE_MAX_LENGTH, ErrorMessage = "Title can't be longer than 200 characters")]
    public string Title { get; set; } = null!;

    [Required]
    [ForeignKey("User")]
    public int UserId { get; set; }
    public User User { get; set; } = null!;

    [Required]
    [ForeignKey("Blog")]
    public int BlogId { get; set; }

    public Blog Blog { get; set; } = null!;

    [Required]
    public DateTime DateTime { get; set; } = DateTime.Now;

    [Required(ErrorMessage = "The field is required")]
    [MinLength(CONTENT_MIN_LENGTH, ErrorMessage = "Content should be at least 5 characters long")]
    public string Content { get; set; } = null!;
}
