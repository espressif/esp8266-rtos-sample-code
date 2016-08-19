/*
 *  LibNoPoll: A websocket library
 *  Copyright (C) 2013 Advanced Software Production Line, S.L.
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation; either version 2.1
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307 USA
 *  
 *  You may find a copy of the license under this software is released
 *  at COPYING file. This is LGPL software: you are welcome to develop
 *  proprietary applications using this library without any royalty or
 *  fee but returning back any change, improvement or addition in the
 *  form of source code, project image, documentation patches, etc.
 *
 *  For commercial support on build Websocket enabled solutions
 *  contact us:
 *          
 *      Postal address:
 *         Advanced Software Production Line, S.L.
 *         Edificio Alius A, Oficina 102,
 *         C/ Antonio Suarez Nº 10,
 *         Alcalá de Henares 28802 Madrid
 *         Spain
 *
 *      Email address:
 *         info@aspl.es - http://www.aspl.es/nopoll
 */
#include "esp_common.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "cJSON.h"

/* Parse text to JSON, then render back to text, and print! */
void Parse_Json(char *text)
{
    char *out;
    cJSON *json;

    json = cJSON_Parse(text);
    if (!json) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
    } else {
        out = cJSON_Print(json);
        cJSON_Delete(json);
        printf("%s\n", out);
        free(out);
    }
}

/* Used by some code below as an example datatype. */
struct record
{
    const char *precision;
    double lat, lon;
    const char *address, *city, *state, *zip, *country;
};

/* Create a bunch of objects as demonstration. */
void create_objects()
{
    cJSON *root, *fmt, *img, *thm, *fld;
    char *out;
    int i; /* declare a few. */
    /* Our "days of the week" array: */
    const char *strings[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    /* Our matrix: */
    int numbers[3][3] = { { 0, -1, 0 }, { 1, 0, 0 }, { 0, 0, 1 } };
    /* Our "gallery" item: */
    int ids[4] = { 116, 943, 234, 38793 };
    /* Our array of "records": */
    struct record fields[2] = { { "zip", 37.7668, -1.223959e+2, "", "SAN FRANCISCO", "CA", "94107", "US" }, { "zip",
            37.371991, -1.22026e+2, "", "SUNNYVALE", "CA", "94085", "US" } };

    /* Here we construct some JSON standards, from the JSON site. */

    /* Our "Video" datatype: */
    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "name", cJSON_CreateString("Jack (\"Bee\") Nimble"));
    cJSON_AddItemToObject(root, "format", fmt = cJSON_CreateObject());
    cJSON_AddStringToObject(fmt, "type", "rect");
    cJSON_AddNumberToObject(fmt, "width", 1920);
    cJSON_AddNumberToObject(fmt, "height", 1080);
    cJSON_AddFalseToObject(fmt, "interlace");
    cJSON_AddNumberToObject(fmt, "frame rate", 24);

    out = cJSON_Print(root);
    cJSON_Delete(root);
    printf("%s\n", out);
    free(out); /* Print to text, Delete the cJSON, print it, release the string. */

    /* Our "days of the week" array: */
    root = cJSON_CreateStringArray(strings, 7);

    out = cJSON_Print(root);
    cJSON_Delete(root);
    printf("%s\n", out);
    free(out);

    /* Our matrix: */
    root = cJSON_CreateArray();
    for (i = 0; i < 3; i++)
        cJSON_AddItemToArray(root, cJSON_CreateIntArray(numbers[i], 3));

    /*	cJSON_ReplaceItemInArray(root,1,cJSON_CreateString("Replacement")); */

    out = cJSON_Print(root);
    cJSON_Delete(root);
    printf("%s\n", out);
    free(out);

    /* Our "gallery" item: */
    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "Image", img = cJSON_CreateObject());
    cJSON_AddNumberToObject(img, "Width", 800);
    cJSON_AddNumberToObject(img, "Height", 600);
    cJSON_AddStringToObject(img, "Title", "View from 15th Floor");
    cJSON_AddItemToObject(img, "Thumbnail", thm = cJSON_CreateObject());
    cJSON_AddStringToObject(thm, "Url", "http:/*www.example.com/image/481989943");
    cJSON_AddNumberToObject(thm, "Height", 125);
    cJSON_AddStringToObject(thm, "Width", "100");
    cJSON_AddItemToObject(img, "IDs", cJSON_CreateIntArray(ids, 4));

    out = cJSON_Print(root);
    cJSON_Delete(root);
    printf("%s\n", out);
    free(out);

    /* Our array of "records": */

    root = cJSON_CreateArray();
    for (i = 0; i < 2; i++) {
        cJSON_AddItemToArray(root, fld = cJSON_CreateObject());
        cJSON_AddStringToObject(fld, "precision", fields[i].precision);
        cJSON_AddNumberToObject(fld, "Latitude", fields[i].lat);
        cJSON_AddNumberToObject(fld, "Longitude", fields[i].lon);
        cJSON_AddStringToObject(fld, "Address", fields[i].address);
        cJSON_AddStringToObject(fld, "City", fields[i].city);
        cJSON_AddStringToObject(fld, "State", fields[i].state);
        cJSON_AddStringToObject(fld, "Zip", fields[i].zip);
        cJSON_AddStringToObject(fld, "Country", fields[i].country);
    }

    /*	cJSON_ReplaceItemInObject(cJSON_GetArrayItem(root,1),"City",cJSON_CreateIntArray(ids,4)); */
    out = cJSON_Print(root);
    cJSON_Delete(root);
    printf("%s\n", out);
    free(out);
    root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "number", 1.0 / 0.0);
    out = cJSON_Print(root);
    cJSON_Delete(root);
    printf("%s\n", out);
    free(out);
}

int json_main(void)
{
    /* a bunch of json: */
    char text1[] =
            "{\n\"name\": \"Jack (\\\"Bee\\\") Nimble\", \n\"format\": {\"type\":       \"rect\", \n\"width\":      1920, \n\"height\":     1080, \n\"interlace\":  false,\"frame rate\": 24\n}\n}";
    char text2[] = "[\"Sunday\", \"Monday\", \"Tuesday\", \"Wednesday\", \"Thursday\", \"Friday\", \"Saturday\"]";
    char text3[] = "[\n    [0, -1, 0],\n    [1, 0, 0],\n    [0, 0, 1]\n	]\n";
    char text4[] =
            "{\n		\"Image\": {\n			\"Width\":  800,\n			\"Height\": 600,\n			\"Title\":  \"View from 15th Floor\",\n			\"Thumbnail\": {\n				\"Url\":    \"http:/*www.example.com/image/481989943\",\n				\"Height\": 125,\n				\"Width\":  \"100\"\n			},\n			\"IDs\": [116, 943, 234, 38793]\n		}\n	}";
    char text5[] =
            "[\n	 {\n	 \"precision\": \"zip\",\n	 \"Latitude\":  37.7668,\n	 \"Longitude\": -122.3959,\n	 \"Address\":   \"\",\n	 \"City\":      \"SAN FRANCISCO\",\n	 \"State\":     \"CA\",\n	 \"Zip\":       \"94107\",\n	 \"Country\":   \"US\"\n	 },\n	 {\n	 \"precision\": \"zip\",\n	 \"Latitude\":  37.371991,\n	 \"Longitude\": -122.026020,\n	 \"Address\":   \"\",\n	 \"City\":      \"SUNNYVALE\",\n	 \"State\":     \"CA\",\n	 \"Zip\":       \"94085\",\n	 \"Country\":   \"US\"\n	 }\n	 ]";

    char text6[] = "<!DOCTYPE html>"
            "<html>\n"
            "<head>\n"
            "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
            "  <style type=\"text/css\">\n"
            "    html, body, iframe { margin: 0; padding: 0; height: 100%; }\n"
            "    iframe { display: block; width: 100%; border: none; }\n"
            "  </style>\n"
            "<title>Application Error</title>\n"
            "</head>\n"
            "<body>\n"
            "  <iframe src=" //s3.amazonaws.com/heroku_pages/error.html">\n"
            "    <p>Application Error</p>\n"
            "  </iframe>\n"
            "</body>\n"
            "</html>\n";

    /* Process each json textblock by parsing, then rebuilding: */
    Parse_Json(text1);
    Parse_Json(text2);
    Parse_Json(text3);
    Parse_Json(text4);
    Parse_Json(text5);
    Parse_Json(text6);

    /* Now some samplecode for building objects concisely: */
    create_objects();

    return 0;
}

static void json_task(void *pvParameters)
{
    json_main();
    while (1) {
        vTaskDelay(200 / portTICK_RATE_MS);
        printf("json_task\n");
    }

    vTaskDelete(NULL);
    printf("delete the json_task\n");
}

/*start the websocket task*/
void json_start(void)
{
    xTaskCreate(json_task, "json_task", 1024, NULL, 4, NULL);
}

/* end-of-file-found */
