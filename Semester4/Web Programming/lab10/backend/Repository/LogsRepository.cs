//https://dev.mysql.com/doc/connector-net/en/connector-net-entityframework-core-example.html
//but different version/install things
using lab10.Models;
using Microsoft.EntityFrameworkCore;

namespace lab10.Repository
{
    public class LogsRepository : DbContext
    {
        public DbSet<Log> Logs { get; set; }
        private readonly IConfiguration Configuration;

        public LogsRepository(IConfiguration configuration)
        {
            Configuration = configuration;
        }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {

            optionsBuilder.UseMySQL(Configuration["ConnectionStrings:DatabaseURL"]);
        }
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);
            modelBuilder.Entity<Log>(entity =>
            {
                entity.HasKey(e => e.id);
                entity.Property(e => e.id).IsRequired();
                entity.Property(e => e.user).IsRequired();
                entity.Property(e => e.data).IsRequired();
                entity.Property(e => e.logDate).IsRequired();
                entity.Property(e => e.severity).IsRequired();
            });
        }
    }
}