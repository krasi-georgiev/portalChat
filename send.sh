#!/bin/bash
curl -X POST -H "Content-Type: application/json" -d '{
  "recipient":{
    "id":"947847768650093"
  },
  "message":{
    "attachment":{
      "type":"template",
      "payload":{
        "template_type":"button",
        "text":"What do you want to do next?",
        "buttons":[
          {
            "type":"account_link",
            "url":"https://dev.portal.vip-consult.co.uk/webhook/messenger/v1",
          }
        ]
      }
    }
  }



}' "https://graph.facebook.com/v2.6/me/messages?access_token=EAAXvqZCDgY5oBAITW6G9yyxYotpZCH5jY1VoaatS0suf3MmwKOdC6Rv2meo64GGuW2VrtAIrcskzaWJ5pf0zI0oGwgxIp9GIoIXJOv5tHQ0qUqsGBZBsAiJcZCDiWC677BBrtEhflU1J0v23rVoNwBab3zEmO1a7bYEESmdj9qZBhyio0x4PZC"
