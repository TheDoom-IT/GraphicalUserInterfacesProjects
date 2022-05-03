namespace blog.Models;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

public class Blog
{
    const int TITLE_MIN_LENGTH = 5;
    const int TITLE_MAX_LENGTH = 50;

    [Key]
    public int Id { get; set; }

    [Required(ErrorMessage = "The field is required")]
    [MinLength(TITLE_MIN_LENGTH, ErrorMessage = "Title should be at least 5 characters long")]
    [MaxLength(TITLE_MAX_LENGTH, ErrorMessage = "Title can't be longer than 50 characters")]
    public string Title { get; set; } = null!;

    [Required]
    [ForeignKey("User")]
    public int UserId { get; set; }
    public User User { get; set; } = null!;

    public List<BlogEntry> BlogEntries { get; set; } = new List<BlogEntry>();
}
