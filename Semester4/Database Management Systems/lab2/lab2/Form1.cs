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
using System.Configuration;

namespace lab1
{
    public partial class Form1 : Form
    {
        private string CONNECTION_STRING = ConfigurationManager.AppSettings["CONNECTION_STRING"];
        
        private readonly string PARENT_TABLE = ConfigurationManager.AppSettings["PARENT_TABLE"];
        private readonly string CHILD_TABLE = ConfigurationManager.AppSettings["CHILD_TABLE"];
        private readonly string FK_CHILD_PARENT = ConfigurationManager.AppSettings["FK_CHILD_PARENT"];
        private string PARENT_ID_COLUMN = ConfigurationManager.AppSettings["PARENT_ID_COLUMN"];
        private string CHILD_FK_COLUMN = ConfigurationManager.AppSettings["CHILD_FK_COLUMN"];

        private DataSet dataSet = new DataSet();
        private SqlConnection dbConnection;
        private SqlDataAdapter dataAdapterParent, dataAdapterChild;
        private BindingSource bindingSourceParent = new BindingSource();
        private BindingSource bindingSourceChild = new BindingSource();
        
        private void InitializeDatabase()
        {
            dbConnection = new SqlConnection(CONNECTION_STRING);
            dataAdapterParent = new SqlDataAdapter($"SELECT * FROM {PARENT_TABLE}", dbConnection);
            dataAdapterChild = new SqlDataAdapter($"SELECT * FROM {CHILD_TABLE}", dbConnection);

            new SqlCommandBuilder(dataAdapterChild);

            dataAdapterParent.Fill(dataSet, PARENT_TABLE);
            dataAdapterChild.Fill(dataSet, CHILD_TABLE);

            dataSet.Relations.Add(new DataRelation(
                FK_CHILD_PARENT,
                dataSet.Tables[PARENT_TABLE].Columns[PARENT_ID_COLUMN],
                dataSet.Tables[CHILD_TABLE].Columns[CHILD_FK_COLUMN]
            ));
        }

        private void InitializeUI()
        {
            this.label1.Text = PARENT_TABLE;
            this.label2.Text = CHILD_TABLE;
            bindingSourceParent.DataSource = dataSet;
            bindingSourceParent.DataMember = PARENT_TABLE;

            bindingSourceChild.DataSource = bindingSourceParent;
            bindingSourceChild.DataMember = FK_CHILD_PARENT;

            UsersGridView.DataSource = bindingSourceParent;
            PostsGridView.DataSource = bindingSourceChild;
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
            SqlCommandBuilder builder = new SqlCommandBuilder(dataAdapterParent);
            builder.GetInsertCommand();
            dataAdapterParent.Update(dataSet, PARENT_TABLE);
            dataAdapterChild.Update(dataSet, CHILD_TABLE);
        }
    }
}
