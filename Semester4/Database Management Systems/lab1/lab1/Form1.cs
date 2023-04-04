using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab1
{
    public partial class Form1 : Form
    {
        private readonly string USERS_TABLE = "USERS";
        private readonly string POSTS_TABLE = "POSTS";
        private readonly string FK_POSTS_USERS = "FK_POSTS_USER_ID";

        private DataSet dataSet = new DataSet();
        private SqlConnection dbConnection;
        private SqlDataAdapter dataAdapterUsers, dataAdapterPosts;
        private BindingSource bindingSourceUsers = new BindingSource();
        private BindingSource bindingSourcePosts = new BindingSource();

        private void InitializeDatabase()
        {
            dbConnection = new SqlConnection("Server=192.168.100.191;Database=SocialMedia;User Id=sa;Password=Password1234;");
            dataAdapterUsers = new SqlDataAdapter($"SELECT * FROM {USERS_TABLE}", dbConnection);
            dataAdapterPosts = new SqlDataAdapter($"SELECT * FROM {POSTS_TABLE}", dbConnection);

            new SqlCommandBuilder(dataAdapterPosts);

            dataAdapterUsers.Fill(dataSet, USERS_TABLE);
            dataAdapterPosts.Fill(dataSet, POSTS_TABLE);

            dataSet.Relations.Add(new DataRelation(
                FK_POSTS_USERS,
                dataSet.Tables[USERS_TABLE].Columns["id"],
                dataSet.Tables[POSTS_TABLE].Columns["userId"]
            ));
        }

        private void InitializeUI()
        {
            bindingSourceUsers.DataSource = dataSet;
            bindingSourceUsers.DataMember = USERS_TABLE;

            bindingSourcePosts.DataSource = bindingSourceUsers;
            bindingSourcePosts.DataMember = FK_POSTS_USERS;

            UsersGridView.DataSource = bindingSourceUsers;
            PostsGridView.DataSource = bindingSourcePosts;
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            InitializeDatabase();
            InitializeUI();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            SqlCommandBuilder builder = new SqlCommandBuilder(dataAdapterUsers);
            builder.GetInsertCommand();
            dataAdapterPosts.Update(dataSet, POSTS_TABLE);
            dataAdapterUsers.Update(dataSet, USERS_TABLE);
        }
    }
}
