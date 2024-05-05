import domain.Student;

import org.junit.jupiter.api.*;

import static org.junit.jupiter.api.Assertions.*;
import repository.StudentXMLRepo;
import service.Service;
import validation.StudentValidator;
import validation.ValidationException;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class StudentTest {
    private StudentXMLRepo studentFileRepository;
    private StudentValidator studentValidator;
    private Service service;

    @BeforeEach
    public void setup() {
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
        this.service = new Service(this.studentFileRepository, this.studentValidator, null, null, null, null);
    }

    @AfterEach
    public void removeXML() {
        new File("fisiere/studentiTest.xml").delete();
    }

    @Test
    public void testGroupBiggerThan0() {
        Student newStudent1 = new Student("1", "Ana", -1, "ana@gmail.com");
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent1));
    }

    @Test
    public void testNumeNotEmpty() {
        Student newStudent1 = new Student("1", "", 931, "ana@gmail.com");
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent1));
    }

    @Test
    public void testNumeNotNull() {
        Student newStudent1 = new Student("1", null, 931, "ana@gmail.com");
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent1));
    }

    @Test
    public void testIdNotEmpty() {
        Student newStudent1 = new Student("", "asfasf", 931, "ana@gmail.com");
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent1));
    }

    @Test
    public void testIdNotNull() {
        Student newStudent1 = new Student(null, "asfasf", 931, "ana@gmail.com");
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent1));
    }

    @Test
    public void testEmailNotEmpty() {
        Student newStudent1 = new Student("3", "asfasf", 931, "");
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent1));
    }

    @Test
    public void testEmailNotNull() {
        Student newStudent1 = new Student("3", "asfasf", 931, null);
        assertThrows(ValidationException.class, () -> this.service.addStudent(newStudent1));
    }

    @Test
    public void testDuplicateId() {
        Student newStudent1 = new Student("3", "asfasf", 931, "a");
        this.service.addStudent(newStudent1);
        assertEquals(newStudent1, this.service.addStudent(newStudent1));
    }

}