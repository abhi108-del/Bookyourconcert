public class BookYourConcert {
    static {
        System.loadLibrary("BookYourConcertLib"); // Load the JNI library
    }

    // Native methods for Booking_Manager
    public native void handleExistingCustomer();
    public native void addNewCustomer();

    // Native methods for Admin
    public native void addVenue(String name, String location, String city, int capacity, String ownerName, int rows, int columns);
    public native void addConcert(String venueName, String concertName, int startHour, int startMinute, int endHour, int endMinute,
                               int day, int month, int year, String language, String rating, String overview);
    public native void deleteVenue(String venueName);
    public native void deleteConcert(String concertName, int startHour, int startMinute);

    // Native methods for saving and loading data
    public native void save();
    public native void start();

    public static void main(String[] args) {
        BookYourConcert system = new BookYourConcert();
        system.start(); // Load data at the beginning

        System.out.println("Welcome to BookYourConcert.");
        System.out.println("We know you are interested in concerts. Go ahead and grab the seats for your favorite concert!\n");

        java.util.Scanner scanner = new java.util.Scanner(System.in);
        
        while (true) {
            System.out.println("1. Login as a Customer");
            System.out.println("2. Login as an Admin");
            System.out.println("3. Signup");
            System.out.println("4. Exit\n-----------------------------------");
            if (!scanner.hasNextInt()) {
                System.out.println("Invalid input\n-----------------------------------");
                scanner.next(); // Clear invalid input
                continue;
            }
            int command = scanner.nextInt();
            scanner.nextLine();

            if (command == 1) {
                system.handleExistingCustomer();
            } else if (command == 2) {
                System.out.print("Enter the secret key: ");
                String key = scanner.next();
                if (!key.equals("123456")) {
                    System.out.println("\nWrong secret key\n-----------------------------------");
                    continue;
                }
                System.out.println("\n-----------------------------------");
                System.out.println("1. Add Venue");
                System.out.println("2. Add Concert");
                System.out.println("3. Delete Venue");
                System.out.println("4. Delete Concert\n-----------------------------------");
                if (!scanner.hasNextInt()) {
                    System.out.println("Invalid input\n-----------------------------------");
                    scanner.next(); // Clear invalid input
                    continue;
                }
                int adminCommand = scanner.nextInt();
                scanner.nextLine();
                if (adminCommand == 1) {
                    System.out.print("Enter Venue Name: ");
                    String name = scanner.next();
                 //   System.out.print("name " + name);
                    System.out.print("Enter Location: ");
                    String location = scanner.next();
                    System.out.print("Enter City: ");
                    String city = scanner.next();
                    System.out.print("Enter Capacity: ");
                    if (!scanner.hasNextInt()) {
                        System.out.println("-----------------------------------\nInvalid input\n-----------------------------------");
                        scanner.next(); // Clear invalid input
                        continue;
                    }
                    int capacity = scanner.nextInt();
                    scanner.nextLine();
                    System.out.print("Enter Owner Name: ");
                    String ownerName = scanner.next();
                    System.out.print("Enter Number of Rows: ");
                    if (!scanner.hasNextInt()) {
                        System.out.println("-----------------------------------\nInvalid input\n-----------------------------------");
                        scanner.next(); // Clear invalid input
                        continue;
                    }
                    int rows = scanner.nextInt();
                    scanner.nextLine();
                    System.out.print("Enter Number of Columns: ");
                    if (!scanner.hasNextInt()) {
                        System.out.println("-----------------------------------\nInvalid input\n-----------------------------------");
                        scanner.next(); // Clear invalid input
                        continue;
                    }
                    int columns = scanner.nextInt();
                    scanner.nextLine();
                    System.out.println("\n-----------------------------------");
                    system.addVenue(name, location, city, capacity, ownerName, rows, columns);
                } else if (adminCommand == 2) {
                    System.out.print("Enter Venue Name: ");
                    String venueName = scanner.next();
                    System.out.print("Enter Concert Name: ");
                    String concertName = scanner.next();
                    System.out.print("Enter Start Time (Hour Minute): ");
                    if (!scanner.hasNextInt()) {
                        System.out.println("-----------------------------------\nInvalid input\n-----------------------------------");
                        scanner.next(); // Clear invalid input
                        continue;
                    }
                    int startHour = scanner.nextInt();
                    if (!scanner.hasNextInt()) {
                        System.out.println("-----------------------------------\nInvalid input\n-----------------------------------");
                        scanner.next(); // Clear invalid input
                        continue;
                    }
                    int startMinute = scanner.nextInt();
                    scanner.nextLine();
                    System.out.print("Enter End Time (Hour Minute): ");
                    if (!scanner.hasNextInt()) {
                        System.out.println("-----------------------------------\nInvalid input\n-----------------------------------");
                        scanner.next(); // Clear invalid input
                        continue;
                    }
                    int endHour = scanner.nextInt();
                    if (!scanner.hasNextInt()) {
                        System.out.println("-----------------------------------\nInvalid input\n-----------------------------------");
                        scanner.next(); // Clear invalid input
                        continue;
                    }
                    int endMinute = scanner.nextInt();
                    scanner.nextLine();
                    System.out.print("Enter Date (Day Month Year): ");
                    if (!scanner.hasNextInt()) {
                        System.out.println("-----------------------------------\nInvalid input\n-----------------------------------");
                        scanner.next(); // Clear invalid input
                        continue;
                    }
                    int day = scanner.nextInt();
                    if (!scanner.hasNextInt()) {
                        System.out.println("-----------------------------------\nInvalid input\n-----------------------------------");
                        scanner.next(); // Clear invalid input
                        continue;
                    }
                    int month = scanner.nextInt();
                    //scanner.nextLine();
                    if (!scanner.hasNextInt()) {
                        System.out.println("-----------------------------------\nInvalid input\n-----------------------------------");
                        scanner.next(); // Clear invalid input
                        continue;
                    }
                    int year = scanner.nextInt();
                    scanner.nextLine();
                    System.out.print("Enter Language: ");
                    String language = scanner.next();
                    System.out.print("Enter Rating: ");
                    String rating = scanner.next();
                    System.out.print("Enter Overview: ");
                    String overview = scanner.next();
                    System.out.println("\n-----------------------------------");
                    system.addConcert(venueName, concertName, startHour, startMinute, endHour, endMinute, day, month, year,
                                   language, rating, overview);
                } else if (adminCommand == 3) {
                    System.out.print("Enter Venue Name: ");
                    String venueName = scanner.next();
                    System.out.println("\n-----------------------------------");
                    system.deleteVenue(venueName);
                }  else if (adminCommand == 4) {
                    System.out.print("Enter Venue Name: ");
                    String venueName = scanner.next();
                    System.out.print("Enter Start Time (Hour Minute): ");
                    if (!scanner.hasNextInt()) {
                        System.out.println("-----------------------------------\nInvalid input\n-----------------------------------");
                        scanner.next(); // Clear invalid input
                        continue;
                    }
                    int startHour = scanner.nextInt();
                    //scanner.nextLine();
                    if (!scanner.hasNextInt()) {
                        System.out.println("-----------------------------------\nInvalid input\n-----------------------------------");
                        scanner.next(); // Clear invalid input
                        continue;
                    }
                    int startMinute = scanner.nextInt();
                    scanner.nextLine();
                    System.out.println("\n-----------------------------------");
                    system.deleteConcert(venueName, startHour, startMinute);
                }
            } else if (command == 3) {
                system.addNewCustomer();
            } else if (command == 4) {
                system.save(); // Save data before exiting
                break;
            }
        }
        scanner.close();
    }

}
