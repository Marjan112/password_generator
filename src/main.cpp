#include <iostream>
#include <random>
#include <unordered_map>

static const std::unordered_map<std::string, const char* (*)()> args = {
    {
        "--lower-alpha",
        []() {
            return "abcdefghijklmnopqrstuvwxyz";
        }
    },
    {
        "--upper-alpha",
        []() {
            return "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        }
    },
    {
        "--num",
        []() {
            return "0123456789";
        }
    },
    {
        "--sym",
        []() {
            return "~`!@#$%^&*()-_+={}[]:|\\;\"'<,>.?/";
        }
    }
};

void print_usage(const char* program_name) {
    std::cout << "Usage: " << program_name << " [options...]\n";
    for(const auto& arg : args) {
        std::cout << "\t" << arg.first << "\n";
    }
}

int main(int argc, char** argv) {
    if(argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    for(int i = 1; i <= argc - 1; ++i) {
        if(args.find(argv[i]) == args.end()) {
            std::cerr << "Unknown command \"" << argv[i] << "\".\n";
            print_usage(argv[0]);
            return 1;
        }
    }

    int password_length;
    char c;
    do {
        std::cout << "Enter password length: ";
        if(scanf("%d", &password_length) != 1) {
            while((c = getchar()) != '\n' && c != EOF);
            continue;
        }
    } while(password_length < 4 || password_length > 255);

    std::string combined;
    std::string prev_arg;

    for(int i = 1; i <= argc - 1; ++i) {
        if(args.find(argv[i]) != args.end() && prev_arg != argv[i]) {
            prev_arg = argv[i];
            combined += args.at(argv[i])();
        }
    }

    std::random_device random_device;
    std::mt19937 random_engine(random_device());
    std::uniform_int_distribution random_picker(0, static_cast<int>(combined.size()) - 1);

    std::string password;
    for(int i = 0; i < password_length; ++i) {
        password.push_back(combined[random_picker(random_engine)]);
    }
    
    std::cout << "Your password is " << password << "\n";
    return 0;
}