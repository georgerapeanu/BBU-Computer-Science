use chrono::offset::Utc;
use chrono::DateTime;
use fake::Fake;
use pwhash::bcrypt;
use std::fs::File;
use std::io::Write;
use std::time::{Duration, SystemTime};

const BATCH_SIZE: usize = 1000;
const USER_COUNT: usize = 10000;
const MANUFACTURER_COUNT: usize = 1000000;
const PRODUCT_COUNT: usize = 1000000;
const REVIEW_COUNT: usize = 10000000;

struct User {
    pub handle: String,
    pub password: String,
    pub activated: bool,
    pub role: String,
}

struct UserProfile {
    pub birthday: String,
    pub email: String,
    pub handle: String,
    pub name: String,
    pub registered_at: String,
}

struct UserPreference {
    pub handle: String,
    pub page_size: usize
}

struct Manufacturer {
    pub description: String,
    pub name: String,
    pub register_date: String,
    pub user_handle: String,
}

struct Product {
    pub description: String,
    pub name: String,
    pub price: f32,
    pub publish_date: String,
    pub weight: u32,
    pub manufacturer_id: usize,
    pub color: String,
}

struct Review {
    pub comment: String,
    pub posted_date: String,
    pub score: u32,
    pub product_id: u32,
    pub user_handle: String,
}

#[derive(Clone)]
struct Role {
    pub name: String,
    pub read_all: bool,
    pub update_all: bool,
    pub delete_all: bool,
    pub read_own: bool,
    pub update_own: bool,
    pub delete_own: bool,
    pub create: bool
}

fn generate_user_handles(total: usize) -> Vec<String> {
    let mut answer: Vec<String> = vec![];
    for i in 0..total {
        let handle: String =
            fake::faker::internet::en::Username().fake::<String>() + &i.to_string();
        answer.push(handle.replace("'", "").replace("\"", ""));
    }
    return answer;
}

fn fake_roles(fd: &mut File) {
    let roles = vec![
        Role {
            name: "visitor".to_string(),
            read_all: true,
            update_all: false,
            delete_all: false,
            read_own: true,
            update_own: false,
            delete_own: false,
            create: false
        },
        Role {
            name: "regular".to_string(),
            read_all: true,
            update_all: false,
            delete_all: false,
            read_own: true,
            update_own: true,
            delete_own: true,
            create: true
        },
        Role {
            name: "moderator".to_string(),
            read_all: true,
            update_all: true,
            delete_all: false,
            read_own: true,
            update_own: true,
            delete_own: true,
            create: true
        },
        Role {
            name: "admin".to_string(),
            read_all: true,
            update_all: true,
            delete_all: true,
            read_own: true,
            update_own: true,
            delete_own: true,
            create: true
        },
    ];
    write!(fd, "INSERT INTO \"role\" (\"name\", \"read_all\", \"update_all\", \"delete_all\", \"read_own\", \"update_own\", \"delete_own\", \"create\") VALUES \n")
        .expect("failure writing");
    for i in 0..roles.len() {
        let role = roles[i].clone();
        write!(
            fd,
            "('{}', {}, {}, {}, {}, {}, {}, {})",
            role.name,
            role.read_all,
            role.update_all,
            role.delete_all,
            role.read_own,
            role.update_own,
            role.delete_own,
            role.create
        )
        .expect("failure writing");
        if i + 1 < roles.len() {
            write!(fd, ",\n").expect("failure writing");
        } else {
            write!(fd, ";\n").expect("failure writing");
        }
    }
    println!("Faked roles");
}

fn fake_users(total: usize, batch: usize, user_handles: &Vec<String>, fd: &mut File) {
    assert!(total % batch == 0);
    assert!(total == user_handles.len());

    let password = bcrypt::hash_with(
        bcrypt::BcryptSetup {
            variant: Some(bcrypt::BcryptVariant::V2a),
            ..Default::default()
        },
        "password",
    )
    .expect("failed encrypting password");

    for i in 0..total {
        if i % batch == 0 {
            println!("Faked users {}/{}", i, total);
            write!(
                fd,
                "INSERT INTO \"user\" (\"handle\", \"password\", \"activated\", \"role\") VALUES \n"
            )
            .expect("failure writing");
        }

        let user = User {
            handle: user_handles[i].clone(),
            password: password.clone(),
            activated: true,
            role: "regular".to_string(),
        };

        write!(
            fd,
            "('{}', '{}', {}, '{}')",
            user.handle,
            user.password,
            if user.activated { "true" } else { "false" },
            user.role
        )
        .expect("error writing an entity");

        if (i + 1) % batch == 0 {
            write!(fd, ";\n").expect("failure writing");
        } else {
            write!(fd, ",\n").expect("failure writing");
        }
    }
}

fn fake_user_profiles(total: usize, batch: usize, user_handles: &Vec<String>, fd: &mut File) {
    assert!(total % batch == 0);
    assert!(total == user_handles.len());

    for i in 0..total {
        if i % batch == 0 {
            println!("Faked user profiles {}/{}", i, total);
            write!(fd, "INSERT INTO \"user_profile\" (\"birthday\", \"email\", \"handle\", \"name\", \"registered_at\") VALUES \n").expect("failure writing");
        }

        let user_profile = UserProfile {
            handle: user_handles[i].clone(),
            name: fake::faker::name::en::Name()
                .fake::<String>()
                .replace("'", "")
                .replace("\"", ""),
            birthday: DateTime::<Utc>::from(
                SystemTime::UNIX_EPOCH
                    + Duration::from_secs((1681000000..1681239961).fake::<u64>()),
            )
            .format("%Y-%m-%d")
            .to_string(),
            email: fake::faker::internet::en::SafeEmail()
                .fake::<String>()
                .replace("'", "")
                .replace("\"", ""),
            registered_at: DateTime::<Utc>::from(
                SystemTime::UNIX_EPOCH
                    + Duration::from_secs((1681000000..1681239961).fake::<u64>()),
            )
            .format("%Y-%m-%d")
            .to_string(),
        };
        write!(
            fd,
            "\n('{}', '{}', '{}', '{}', '{}')",
            user_profile.birthday,
            user_profile.email,
            user_profile.handle,
            user_profile.name,
            user_profile.registered_at
        )
        .expect("failure writing");

        if (i + 1) % batch == 0 {
            write!(fd, ";\n").expect("failure writing");
        } else {
            write!(fd, ",\n").expect("failure writing");
        }
    }
}

fn fake_user_preferences(total: usize, batch: usize, user_handles: &Vec<String>, fd: &mut File) {
    assert!(total % batch == 0);
    assert!(total == user_handles.len());

    for i in 0..total {
        if i % batch == 0 {
            println!("Faked user profiles {}/{}", i, total);
            write!(fd, "INSERT INTO \"user_preference\" (\"handle\", \"page_size\") VALUES \n").expect("failure writing");
        }

        let user_preference = UserPreference{
            handle: user_handles[i].clone(),
            page_size: 10
        };

        write!(
            fd,
            "\n('{}', {})",
            user_preference.handle, 
            user_preference.page_size
        )
        .expect("failure writing");

        if (i + 1) % batch == 0 {
            write!(fd, ";\n").expect("failure writing");
        } else {
            write!(fd, ",\n").expect("failure writing");
        }
    }
}

fn fake_manufacturers(total: usize, batch: usize, user_handles: &Vec<String>, fd: &mut File) {
    assert!(total % batch == 0);

    for i in 0..total {
        if i % batch == 0 {
            println!("Faked manufacturers {}/{}", i, total);
            write!(fd, "INSERT INTO \"manufacturer\" (\"description\", \"name\", \"register_date\", \"user_handle\") VALUES \n").expect("failure writing");
        }

        let manufacturer = Manufacturer {
            description: fake::faker::lorem::en::Sentence(1..5)
                .fake::<String>()
                .replace("'", "")
                .replace("\"", ""),
            name: fake::faker::company::en::CompanyName()
                .fake::<String>()
                .replace("'", "")
                .replace("\"", ""),
            register_date: DateTime::<Utc>::from(
                SystemTime::UNIX_EPOCH
                    + Duration::from_secs((1681000000..1681239961).fake::<u64>()),
            )
            .format("%Y-%m-%d")
            .to_string(),
            user_handle: user_handles[(0..user_handles.len()).fake::<usize>()].clone(),
        };

        write!(
            fd,
            "\n('{}', '{}', '{}', '{}')",
            manufacturer.description,
            manufacturer.name,
            manufacturer.register_date,
            manufacturer.user_handle
        )
        .expect("failure writing");

        if (i + 1) % batch == 0 {
            write!(fd, ";\n").expect("failure writing");
        } else {
            write!(fd, ",\n").expect("failure writing");
        }
    }
}

fn fake_products(total: usize, batch: usize, fd: &mut File) {
    assert!(total % batch == 0);

    for i in 0..total {
        if i % batch == 0 {
            println!("Faked products {}/{}", i, total);
            write!(fd, "INSERT INTO \"product\" (\"description\", \"name\", \"price\", \"publish_date\", \"weight\", \"manufacturer_id\", \"color\") VALUES \n").expect("failure writing");
        }

        let name: String = (&vec![
            String::from("watch"),
            String::from("car"),
            String::from("book"),
            String::from("table"),
            String::from("crayon"),
            String::from("rose"),
            String::from("glasses"),
            String::from("glass"),
            String::from("cheese"),
            String::from("milk"),
        ])[(0..=9).fake::<usize>()]
        .to_string();
        let color: String = (&vec![
            String::from("RED"),
            String::from("BLUE"),
            String::from("GREEN"),
        ])[(0..=2).fake::<usize>()]
        .to_string();

        let product = Product {
            description: fake::faker::lorem::en::Sentence(1..5)
                .fake::<String>()
                .replace("'", "")
                .replace("\"", ""),
            name,
            price: (100..100000).fake::<u32>() as f32 / 100 as f32,
            publish_date: DateTime::<Utc>::from(
                SystemTime::UNIX_EPOCH
                    + Duration::from_secs((1681000000..1681239961).fake::<u64>()),
            )
            .format("%Y-%m-%d")
            .to_string(),
            weight: (10..100).fake::<u32>(),
            manufacturer_id: (1..=MANUFACTURER_COUNT).fake::<usize>(),
            color,
        };

        write!(
            fd,
            "\n('{}', '{}', {}, '{}', '{}', {}, '{}')",
            product.description,
            product.name,
            product.price,
            product.publish_date,
            product.weight,
            product.manufacturer_id,
            product.color
        )
        .expect("failure writing");

        if (i + 1) % batch == 0 {
            write!(fd, ";\n").expect("failure writing");
        } else {
            write!(fd, ",\n").expect("failure writing");
        }
    }
}

fn fake_reviews(total: usize, batch: usize, user_handles: &Vec<String>, fd: &mut File) {
    assert!(total % batch == 0);

    let mut user_id = 1;
    let mut product_id = 1;

    for i in 0..total {
        if i % batch == 0 {
            println!("Faked reviews {}/{}", i, total);
            write!(fd, "INSERT INTO \"review\" (\"comment\", \"posted_date\", \"score\", \"product_id\", \"user_handle\") VALUES \n").expect("failure writing");
        }

        let review = Review {
            comment: fake::faker::lorem::en::Sentence(1..5)
                .fake::<String>()
                .replace("'", "")
                .replace("\"", ""),
            posted_date: DateTime::<Utc>::from(
                SystemTime::UNIX_EPOCH
                    + Duration::from_secs((1681000000..1681239961).fake::<u64>()),
            )
            .to_string(),
            score: (1..=5).fake::<u32>(),
            product_id,
            user_handle: user_handles[user_id - 1].clone(),
        };

        write!(
            fd,
            "\n('{}', '{}', {}, {}, '{}')",
            review.comment, review.posted_date, review.score, review.product_id, review.user_handle
        )
        .expect("failure writing");

        user_id += 1;

        if user_id > USER_COUNT {
            user_id = 1;
            product_id += 1;
        }

        if (i + 1) % batch == 0 {
            write!(fd, ";\n").expect("failure writing");
        } else {
            write!(fd, ",\n").expect("failure writing");
        }
    }
}

fn generate_meta_users(fd: &mut File) {
    let password = bcrypt::hash_with(
        bcrypt::BcryptSetup {
            variant: Some(bcrypt::BcryptVariant::V2a),
            ..Default::default()
        },
        "password",
    )
    .expect("failed encrypting password");

    writeln!(fd, "INSERT INTO \"user\" VALUES ('admin', '{}', true, 'admin');", password).expect("Failure writing");
    writeln!(fd, "INSERT INTO \"user\" VALUES ('moderator', '{}', true, 'moderator');", password).expect("Failure writing");
    writeln!(fd, "INSERT INTO \"user\" VALUES ('regular', '{}', true, 'regular');", password).expect("Failure writing");
    writeln!(fd, "INSERT INTO \"user\" VALUES ('visitor', '{}', true, 'visitor');", password).expect("Failure writing");
    
    writeln!(fd, "INSERT INTO \"user_profile\" VALUES ('2003-02-03', 'email', 'admin', 'admin', '2023-02-03');").expect("Failure writing");
    writeln!(fd, "INSERT INTO \"user_profile\" VALUES ('2003-02-03', 'email', 'moderator', 'moderator', '2023-02-03');").expect("Failure writing");
    writeln!(fd, "INSERT INTO \"user_profile\" VALUES ('2003-02-03', 'email', 'regular', 'regular', '2023-02-03');").expect("Failure writing");
    writeln!(fd, "INSERT INTO \"user_profile\" VALUES ('2003-02-03', 'email', 'visitor', 'visitor', '2023-02-03');").expect("Failure writing");

    writeln!(fd, "INSERT INTO \"user_preference\" VALUES ('admin', 10);").expect("Failure writing");
    writeln!(fd, "INSERT INTO \"user_preference\" VALUES ('moderator', 10);").expect("Failure writing");
    writeln!(fd, "INSERT INTO \"user_preference\" VALUES ('regular', 10);").expect("Failure writing");
    writeln!(fd, "INSERT INTO \"user_preference\" VALUES ('visitor', 10);").expect("Failure writing");
    
    println!("Generated metausers");
}

fn main() {
    let mut file = File::create("./schema.sql").expect("failure creating file");

    writeln!(file, "TRUNCATE TABLE \"role\" CASCADE;").expect("failure writing");
    writeln!(file, "TRUNCATE TABLE \"review\" RESTART IDENTITY CASCADE;").expect("failure writing");
    writeln!(
        file,
        "TRUNCATE TABLE \"user_profile\" RESTART IDENTITY CASCADE;"
    )
    .expect("failure writing");
    writeln!(file, "TRUNCATE TABLE \"user\" RESTART IDENTITY CASCADE;").expect("failure writing");
    writeln!(file, "TRUNCATE TABLE \"user_preference\" CASCADE;").expect("failure writing");
    writeln!(file, "TRUNCATE TABLE \"product\" RESTART IDENTITY CASCADE;")
        .expect("failure writing");
    writeln!(
        file,
        "TRUNCATE TABLE \"manufacturer\" RESTART IDENTITY CASCADE;"
    )
    .expect("failure writing");

    let user_handles = generate_user_handles(USER_COUNT);

    fake_roles(&mut file);
    generate_meta_users(& mut file);
    fake_users(USER_COUNT, BATCH_SIZE, &user_handles, &mut file);
    fake_user_profiles(USER_COUNT, BATCH_SIZE, &user_handles, &mut file);
    fake_user_preferences(USER_COUNT, BATCH_SIZE, &user_handles, &mut file);
    fake_manufacturers(MANUFACTURER_COUNT, BATCH_SIZE, &user_handles, &mut file);
    fake_products(PRODUCT_COUNT, BATCH_SIZE, &mut file);
    fake_reviews(REVIEW_COUNT, BATCH_SIZE, &user_handles, &mut file);
}
