import curent.Curent;
import domain.Nota;
import domain.Student;
import domain.Tema;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import repository.NotaXMLRepo;
import repository.StudentXMLRepo;
import repository.TemaXMLRepo;
import service.Service;
import validation.NotaValidator;
import validation.StudentValidator;
import validation.TemaValidator;
import validation.ValidationException;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDate;

import static org.junit.jupiter.api.Assertions.*;


public class StudentTemaNotaIntegrationTest {
    private TemaXMLRepo temaFileRepository;
    private TemaValidator temaValidator;
    private StudentXMLRepo studentFileRepository;
    private StudentValidator studentValidator;

    private NotaXMLRepo notaFileRepository;
    private NotaValidator notaValidator;

    private Service service;

    @BeforeEach
    public void setup() {
        {
            File xml = new File("fisiere/temaTest.xml");
            try (BufferedWriter writer = new BufferedWriter(new FileWriter(xml))) {
                writer.write("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n" +
                        "<inbox>\n" +
                        "\n" +
                        "</inbox>");
                writer.flush();
            } catch (IOException e) {
                e.printStackTrace();
            }
            this.temaFileRepository = new TemaXMLRepo("fisiere/temaTest.xml");
            this.temaValidator = new TemaValidator();
        }
        {
            File xml = new File("fisiere/studentiTest.xml");
            try (BufferedWriter writer = new BufferedWriter(new FileWriter(xml))) {
                writer.write("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n" +
                        "<inbox>\n" +
                        "\n" +
                        "</inbox>");
                writer.flush();
            }
            catch (IOException e) {
                e.printStackTrace();
            }
            this.studentFileRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
            this.studentValidator = new StudentValidator();
        }
        {
            File xml = new File("fisiere/notaTest.xml");
            try (BufferedWriter writer = new BufferedWriter(new FileWriter(xml))) {
                writer.write("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n" +
                        "<inbox>\n" +
                        "\n" +
                        "</inbox>");
                writer.flush();
            }
            catch (IOException e) {
                e.printStackTrace();
            }
            this.notaFileRepository = new NotaXMLRepo("fisiere/notaTest.xml");
            this.notaValidator = new NotaValidator(this.studentFileRepository, this.temaFileRepository);
        }
        this.service = new Service(studentFileRepository, studentValidator, temaFileRepository, temaValidator, notaFileRepository, notaValidator);
        studentFileRepository.save(new Student("333", "333", 2, "333"));
        temaFileRepository.save(new Tema("333", "333", 1, 1));
    }

    @AfterEach
    public void removeXML() {
        new File("fisiere/studentTest.xml").delete();
        new File("fisiere/temaTest.xml").delete();
        new File("fisiere/notaTest.xml").delete();
    }

    @Test
    public void testAddTema() {
        Tema tema = new Tema("222", "a", 1, 1);
        assertNull(service.addTema(tema));
    }

    @Test
    public void testAddStudent() {
        Student student = new Student("222", "Ana", 931, "ana@gmail.com");
        assertNull(service.addStudent(student));
    }

    @Test
    public void testAddStudentTemaNota() {

        Student student = new Student("222", "Ana", 931, "ana@gmail.com");
        Tema tema = new Tema("222", "a", 1, 1);
        Nota nota = new Nota("222", "222", "222", 10, Curent.getStartDate().plusDays(7));

        assertNull(service.addStudent(student));
        assertNull(service.addTema(tema));
        assertEquals(service.addNota(nota, "bine"), 10.0);

        service.deleteNota("333");
        service.deleteStudent("333");
        service.deleteTema("333");
    }

    @Test
    public void testAddNota() {

        Nota nota = new Nota("333", "333", "333", 10, Curent.getStartDate().plusDays(7));
        assertEquals(service.addNota(nota, "bine"), 10.0);

        service.deleteNota("333");
        service.deleteStudent("333");
        service.deleteTema("333");
    }


}
