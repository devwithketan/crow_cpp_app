
#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#include "crow.h"
#include <fstream>
#include <sstream>

//#include "crow_all.h"

int main()
{
	crow::SimpleApp app; //define your crow application

	// Route to handle file uploads and store them on the server
	CROW_ROUTE(app, "/uploadfile")
		.methods(crow::HTTPMethod::Post)([](const crow::request& req) {
		crow::multipart::message file_message(req);
		//std::ostringstream os;
		for (const auto& part : file_message.part_map)
		{
			const auto& part_name = part.first;
			const auto& part_value = part.second;
			CROW_LOG_DEBUG << "Part: " << part_name;
			if ("InputFile" == part_name)
			{
				// Extract the file name
				auto headers_it = part_value.headers.find("Content-Disposition");
				if (headers_it == part_value.headers.end())
				{
					CROW_LOG_ERROR << "No Content-Disposition found";
					return crow::response(400);
				}
				auto params_it = headers_it->second.params.find("filename");
				if (params_it == headers_it->second.params.end())
				{
					CROW_LOG_ERROR << "Part with name \"InputFile\" should have a file";
					return crow::response(400);
				}
				const std::string outfile_name{ params_it->second };

				for (const auto& part_header : part_value.headers)
				{
					const auto& part_header_name = part_header.first;
					const auto& part_header_val = part_header.second;
					CROW_LOG_DEBUG << "Header: " << part_header_name << '=' << part_header_val.value;
					for (const auto& param : part_header_val.params)
					{
						const auto& param_key = param.first;
						const auto& param_val = param.second;
						CROW_LOG_DEBUG << " Param: " << param_key << ',' << param_val;
					}
				}

				// Create a new file with the extracted file name and write file contents to it
				std::ofstream out_file(outfile_name);
				if (!out_file)
				{
					CROW_LOG_ERROR << " Write to file failed\n";
					continue;
				}
				out_file << part_value.body;
				out_file.close();
				CROW_LOG_INFO << " Contents written to " << outfile_name << '\n';
			}
			else
			{
				//os << part_value.body;
				CROW_LOG_DEBUG << " Value: " << part_value.body << '\n';

			}
		}
		//res.write(os.str());
		//res.end();
		return crow::response(200);
	});

	// Handle POST request to create a downloadable file
	CROW_ROUTE(app, "/process-file").methods("POST"_method)
		([](const crow::request& req) {
		// Example: Let's pretend we are generating a file from POST data
		// Get the request body (assume it's JSON for simplicity)
		auto body = req.body;

		// Create a new file to send to the client
		std::string file_content = "This is a downloadable file.\n";
		file_content += "Received body: " + body;

		// Save the content to a temporary file
		std::string filename = "downloaded_file.txt";
		std::ofstream outfile(filename);
		if (!outfile) {
			return crow::response(500, "Failed to create file");
		}
		outfile << file_content;
		outfile.close();

		// Read the file's content for sending it in the response
		std::ifstream file_to_send(filename, std::ios::binary);
		if (!file_to_send) {
			return crow::response(500, "Failed to read file");
		}

		std::stringstream buffer;
		buffer << file_to_send.rdbuf();
		file_to_send.close();

		// Set headers to instruct the browser to download the file
		crow::response res(buffer.str());
		res.add_header("Content-Disposition", "attachment; filename=" + filename);  // Force download
		res.add_header("Content-Type", "application/octet-stream");  // You can adjust Content-Type based on the file type

		// Send the file content as the response
		return res;
	});

	////define your endpoint at the root directory
	CROW_ROUTE(app, "/")([]() {
		return "Hello world";
		});

	CROW_ROUTE(app, "/add/<int>/<int>")
		([](crow::response& res, int a, int b) {
		std::ostringstream os;
		os << a + b;
		res.write(os.str());
		res.end();
	});

	//set the port, set the app to run on multiple threads, and run the app
	app.bindaddr("127.0.0.1").port(18080).multithreaded().run();
}
