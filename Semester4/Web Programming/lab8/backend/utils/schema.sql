CREATE TABLE Logs (
  id INT AUTO_INCREMENT PRIMARY KEY,
  severity VARCHAR(32) NOT NULL,
  logDate DATE NOT NULL,
  user VARCHAR(32) NOT NULL,
  data VARCHAR(256) NOT NULL
)
