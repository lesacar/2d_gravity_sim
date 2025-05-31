#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <string>
#include <httplib.h>
#include <json.hpp>

int main() {
    printf("gigafry_bot starting...\n\n");

    // Get API key
    const char* api_key = std::getenv("DEEPSEEK_API_KEY");
    if (!api_key) {
        std::cerr << "Error: Missing API key in environment" << std::endl;
        return 1;
    }

    // Setup HTTP client
    httplib::SSLClient cli("api.deepseek.com", 443);
    cli.set_default_headers({
        {"Authorization", std::string("Bearer ") + api_key},
        {"Content-Type", "application/json"}
    });

    // Create request data
    nlohmann::json request = {
        {"model", "deepseek-chat"},
        {"messages", {{{"role", "user"}, {"content", "9.11 and 9.8, which is greater?"}}}},
            {"stream", true}
        };

    // Make the request (non-streaming version)
    auto res = cli.Post("/v1/chat/completions", request.dump(), "application/json");
    if (!res || res->status != 200) {
        std::cerr << "Request failed" << std::endl;
        return 1;
    }

    // Process the response as if it were streamed
    std::string buffer = res->body;
    size_t start_pos = 0;

    while (start_pos < buffer.length()) {
        // Find next newline character
        size_t end_pos = buffer.find('\n', start_pos);
        if (end_pos == std::string::npos) break;

        // Extract single line
        std::string line = buffer.substr(start_pos, end_pos - start_pos);
        start_pos = end_pos + 1;

        // Skip empty lines and non-data lines
        if (line.empty() || line.substr(0, 6) != "data: ") continue;

        // Extract JSON payload
        std::string json_str = line.substr(6);
        if (json_str == "[DONE]") break;

        // Parse JSON
        auto json = nlohmann::json::parse(json_str, nullptr, false);
        if (json.is_discarded()) continue;  // Skip invalid JSON

        // Extract and print content
        if (json.contains("choices") && 
            json["choices"].is_array() &&
            !json["choices"].empty() &&
            json["choices"][0].contains("delta") &&
            json["choices"][0]["delta"].contains("content")) {
            std::cout << json["choices"][0]["delta"]["content"].get<std::string>() << std::flush;
        }

        // Exit if finish reason is set
        if (json.contains("choices") && 
            !json["choices"][0]["finish_reason"].is_null()) {
            break;
        }
    }

    printf("\n\nStream completed\n");
    return 0;
}
