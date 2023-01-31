//Petar Ubavic Jovan Ikic
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#define DEVICE_NAME "baza"
#define MAX_STUDENTS 10
#define MAX_INPUT_LENGTH 30

typedef struct student {
  char name[MAX_INPUT_LENGTH];
  char surname[MAX_INPUT_LENGTH];
  char index[MAX_INPUT_LENGTH];
  int score;
} student_t;

student_t students[MAX_STUDENTS];
int current_student_count = 0;
int device_number = 0;

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = {
  .read = device_read,
  .write = device_write,
  .open = device_open,
  .release = device_release
};

static int __init baza_init(void) {
  int t = register_chrdev(0, DEVICE_NAME, &fops);
  if (t < 0) {
    printk(KERN_ALERT "Baza: error registering device\n");
  } else {
    printk(KERN_INFO "Baza: device registered with major number %d\n", t);
  }
  return t;
}

static void __exit baza_exit(void) {
  unregister_chrdev(MAJOR(device_number), DEVICE_NAME);
  printk(KERN_INFO "Baza: device unregistered\n");
}

static int device_open(struct inode *inode, struct file *file) {
  printk(KERN_INFO "Baza: device opened\n");
  return 0;
}

static int device_release(struct inode *inode, struct file *file) {
  printk(KERN_INFO "Baza: device released\n");
  return 0;
}

static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset) {
  int error_count = 0;
  char message[MAX_INPUT_LENGTH * 4];
  int i;
  
  for (i = 0; i < current_student_count; i++) {
    sprintf(message + strlen(message), "%s,%s,%s,%d\n", students[i].name, students[i].surname, students[i].index, students[i].score);
  }

  error_count = copy_to_user(buffer, message, strlen(message));
  if (error_count == 0) {
    printk(KERN_INFO "Baza: sent %d characters to the user\n", (int)strlen(message));

return strlen(message);
} else {
printk(KERN_INFO "Baza: failed to send %d characters to the user\n", error_count);
return -EFAULT;
}
}

static ssize_t device_write(struct file *filp, const char *buffer, size_t length, loff_t *offset) {
int i, input_index = 0, comma_count = 0, input_length = 0;
char input[MAX_INPUT_LENGTH];
char *parsed;

if (current_student_count == MAX_STUDENTS) {
printk(KERN_INFO "Baza: database is full\n");
return -ENOSPC;
}

input_length = length > MAX_INPUT_LENGTH ? MAX_INPUT_LENGTH : length;
if (copy_from_user(input, buffer, input_length)) {
return -EFAULT;
}

for (i = 0; i < input_length; i++) {
if (input[i] == ',') {
comma_count++;
input[i] = '\0';
}
if (comma_count == 0) {
  strcpy(students[current_student_count].name, input + input_index);
} else if (comma_count == 1) {
  strcpy(students[current_student_count].surname, input + input_index);
} else if (comma_count == 2) {
  strcpy(students[current_student_count].index, input + input_index);
} else if (comma_count == 3) {
  students[current_student_count].score = (int) simple_strtol(input + input_index, &parsed, 10);
}

if (input[i] == '\0') {
  input_index = i + 1;
}
}

current_student_count++;
printk(KERN_INFO "Baza: added new student: %s,%s,%s,%d\n", students[current_student_count - 1].name, students[current_student_count - 1].surname, students[current_student_count - 1].index, students[current_student_count - 1].score);
return length;
}

module_init(baza_init);
module_exit(baza_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");
MODULE_DESCRIPTION("Student database driver");
