class Roommate:
    def __init__(self):
        self.name = ""
        self.age = 0
        self.student_id = ""
        self.height = ""
        self.nick_name = ""
        self.hobby = ""
        self.course = ""
        self.college = ""
    
    def display_info(self):
        print(" Roommate Information ")
        print("--------------------------")
        print(f"Name: {self.name}")
        print(f"Age: {self.age}")
        print(f"Student ID: {self.student_id}")
        print(f"Height: {self.height}")
        print(f"Nickname: {self.nick_name}")
        print(f"Hobby: {self.hobby}")
        print(f"Course: {self.course}")
        print(f"College: {self.college}")
        print("--------------------------")
        print("That is my amazing friend!")

def main():
    my_roommate = Roommate()
    
    my_roommate.name = "Gerald Asmin"
    my_roommate.age = 21
    my_roommate.student_id = "ENC221-0088/2024"
    my_roommate.height = "180cm"
    my_roommate.nick_name = "palsa"
    my_roommate.hobby = "dancing"
    my_roommate.course = "Geomatic Engineering"
    my_roommate.college = "COETEC"
    
    my_roommate.display_info()

if __name__ == "__main__":
    main()
