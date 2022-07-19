const char first[] PROGMEM = R"=====(
<!DOCTYPE html>
<title>Smart Queue</title>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        @media only screen and (max-width: 600px) {
            .login-page {
                width: 360px;
                padding: 40% 0 0;
                margin: auto;
            }
        }
        
        @media only screen and (min-width: 768px) {
            .login-page {
                width: 360px;
                padding: 8% 0 0;
                margin: auto;
            }
        }
        
        .form {
            font-family: "Roboto", serif;
            font-size: 19.2px;
            position: relative;
            z-index: 1;
            border-radius: 5px;
            background: #FFFFFF;
            max-width: 360px;
            margin: 0 auto 100px;
            padding: 45px;
            text-align: left;
            box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 10px 10px 0 rgba(0, 0, 0, 0.24);
            opacity: 100;
        }
        
        .form input[type=number] {
            font-family: "Roboto", serif;
            outline: 0;
            background: #f2f2f2;
            width: 100%;
            border: 0;
            margin: 0 0 15px;
            padding: 15px;
            box-sizing: border-box;
            font-size: 14px;
        }
        
        .form input[type="submit"] {
            font-family: "Roboto", serif;
            text-transform: uppercase;
            outline: 0;
            background: #2196f3;
            width: 100%;
            border: none;
            border-radius: 10px;
            padding: 15px;
            color: #FFFFFF;
            font-size: 14px;
            -webkit-transition: all 0.3 ease;
            transition: all 0.3 ease;
            cursor: pointer;
        }
        
        .form input[type="submit"]:hover,
        .form input[type="submit"]:active,
        .form input[type="submit"]:focus {
            background: #0d47a1;
        }
        
        .form .login-form {
            display: none;
        }
        
        .form .message {
            margin: 15px 0 0;
            color: #b3b3b3;
            font-size: 15px;
        }
        
        .form .message a {
            color: #2196f3;
            text-decoration: none;
        }
        
        body {
            background: #42a5f5;
            /* fallback for old browsers */
        }
    </style>

</head>

<body>
    <div class="login-page">
        <div class="form">
            <form method="POST" action="checkpass.php" class="register-form" id="1">
                <h1>Smart Queue</h1>
                <p>Welcome to Virtual Queue service.<br>To get the token please enter your phone number and continue.</p>
                <input type="number" placeholder="Phone number" name="data" />
                <input type="submit" name="action" value="Get OTP" />
                <p class="message">Already have an OTP? <a href="#" onclick=togglerl()>Get your token</a></p>
            </form>
            <form method="POST" action="checkotp.php" class="login-form" id="2">
                <h1>Smart Queue</h1>
                <p>To get your token please enter OTP.</p>
                <input type="number" placeholder="OTP" name="otp" />
                <input type="submit" name="action" value="Verify OTP" />
                <p class="message">Didn't get the code? <a href="#" onclick=togglelr()> Resend it</a></p>
            </form>
        </div>
    </div>

    <script>
        function togglerl() {
            document.getElementById(1).style.display = "none";
            document.getElementById(2).style.display = "block";
        }

        function togglelr() {
            document.getElementById(2).style.display = "none";
            document.getElementById(1).style.display = "block";

        }
    </script>
</body>

</html>
)=====";
const char otpp[] PROGMEM = R"=====(
<!DOCTYPE html>
<title>Smart Queue</title>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        @media only screen and (max-width: 600px) {
            .login-page {
                width: 360px;
                padding: 40% 0 0;
                margin: auto;
            }
        }
        
        @media only screen and (min-width: 768px) {
            .login-page {
                width: 360px;
                padding: 8% 0 0;
                margin: auto;
            }
        }
        
        .form {
            font-family: "Roboto", serif;
            font-size: 19.2px;
            position: relative;
            z-index: 1;
            border-radius: 5px;
            background: #FFFFFF;
            max-width: 360px;
            margin: 0 auto 100px;
            padding: 45px;
            text-align: left;
            box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 10px 10px 0 rgba(0, 0, 0, 0.24);
            opacity: 100;
        }
        
        .form input[type=number] {
            font-family: "Roboto", serif;
            outline: 0;
            background: #f2f2f2;
            width: 100%;
            border: 0;
            margin: 0 0 15px;
            padding: 15px;
            box-sizing: border-box;
            font-size: 14px;
        }
        
        .form input[type="submit"] {
            font-family: "Roboto", serif;
            text-transform: uppercase;
            outline: 0;
            background: #2196f3;
            width: 100%;
            border: none;
            border-radius: 10px;
            padding: 15px;
            color: #FFFFFF;
            font-size: 14px;
            -webkit-transition: all 0.3 ease;
            transition: all 0.3 ease;
            cursor: pointer;
        }
        
        .form input[type="submit"]:hover,
        .form input[type="submit"]:active,
        .form input[type="submit"]:focus {
            background: #0d47a1;
        }
        
        .form .register-form {
            display: none;
        }
        
        .form .message {
            margin: 15px 0 0;
            color: #b3b3b3;
            font-size: 15px;
        }
        
        .form .message a {
            color: #2196f3;
            text-decoration: none;
        }
        
        body {
            background: #42a5f5;
            /* fallback for old browsers */
        }
    </style>

</head>

<body>
    <div class="login-page">
        <div class="form">
            <form method="POST" action="checkpass.php" class="register-form" id="1">
                <h1>Smart Queue</h1>
                <p>Welcome to Virtual Queue service.<br>To get the token please enter your phone number and continue.</p>
                <input type="number" placeholder="Phone number" name="data" />
                <input type="submit" name="action" value="Get OTP" />
                <p class="message">Already have an OTP? <a href="#" onclick=togglerl()>Get your token</a></p>
            </form>
            <form method="POST" action="checkotp.php" class="login-form" id="2">
                <h1>Smart Queue</h1>
                <p>To get your token please enter OTP.</p>
                <input type="number" placeholder="OTP" name="otp" />
                <input type="submit" name="action" value="Verify OTP" />
                <p class="message">Didn't get the code? <a href="#" onclick=togglelr()> Resend it</a></p>
            </form>
        </div>
    </div>

    <script>
        function togglerl() {
            document.getElementById(1).style.display = "none";
            document.getElementById(2).style.display = "block";
        }

        function togglelr() {
            document.getElementById(2).style.display = "none";
            document.getElementById(1).style.display = "block";

        }
    </script>
</body>

</html>
)=====";

const char already[] PROGMEM = R"=====(
<!DOCTYPE html>
<title>Smart Queue</title>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
    @media only screen and (max-width: 600px) {
            .login-page {
                width: 360px;
                padding: 40% 0 0;
                margin: auto;
            }
        }
        
        @media only screen and (min-width: 768px) {
            .login-page {
                width: 360px;
                padding: 15% 0 0;
                margin: auto;
            }
        }
        
        .form {
            font-family: "Roboto", serif;
            position: relative;
            z-index: 1;
            border-radius: 5px;
            background: #FFFFFF;
            max-width: 360px;
            margin: 0 auto 100px;
            padding: 45px;
            text-align: left;
            box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 10px 10px 0 rgba(0, 0, 0, 0.24);
        }
        
        body {
            background: #42a5f5;
        }
    }
    </style>

</head>

<body>
    <div class="login-page">
        <div class="form">
            <form method="POST" action="checkotp.php" class="login-form">
                <h1>Smart Queue</h1>
                <p style="text-align: justify; font-size: 20px;">You are already registered.</p>
            </form>
        </div>
    </div>
</body>

</html>
)=====";
const char invalid[] PROGMEM = R"=====(
<!DOCTYPE html>
<title>Smart Queue</title>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
    @media only screen and (max-width: 600px) {
            .login-page {
                width: 360px;
                padding: 40% 0 0;
                margin: auto;
            }
        }
        
        @media only screen and (min-width: 768px) {
            .login-page {
                width: 360px;
                padding: 15% 0 0;
                margin: auto;
            }
        }
        
        .form {
            font-family: "Roboto", serif;
            position: relative;
            z-index: 1;
            border-radius: 5px;
            background: #FFFFFF;
            max-width: 360px;
            margin: 0 auto 100px;
            padding: 45px;
            text-align: left;
            box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 10px 10px 0 rgba(0, 0, 0, 0.24);
        }
        
        .form input {
            font-family: "Roboto", serif;
            outline: 0;
            background: #f2f2f2;
            width: 100%;
            border: 0;
            margin: 0 0 15px;
            padding: 15px;
            box-sizing: border-box;
            font-size: 14px;
        }
        
        .form input[type=submit] {
            font-family: "Roboto", serif;
            text-transform: uppercase;
            outline: 0;
            background: #2196f3;
            width: 100%;
            border: none;
            border-radius: 10px;
            padding: 15px;
            color: #FFFFFF;
            font-size: 14px;
            -webkit-transition: all 0.3 ease;
            transition: all 0.3 ease;
            cursor: pointer;
        }
        
        .form input[type=submit] :hover,
        .form input[type=submit] :active,
        .form input[type=submit] :focus {
            background: #0d47a1;
        }
        
        body {
            background: #42a5f5;
            /* fallback for old browsers */
        }
        
         ::placeholder {
            color: red;
            opacity: 1;
        }
    }
    </style>

</head>

<body>
    <div class="login-page">
        <div class="form">
            <form action="172.128.128.100" method="GET">
                <h2>Smart Queue</h2>
                <input type="text" placeholder="Invalid OTP !" name="otp" disabled />
                <input type="submit" Value="Try Again" />
            </form>
        </div>
    </div>
</body>

</html>
)=====";

const char tok1[] PROGMEM = R"=====(
<!DOCTYPE html>
<title>Smart Queue</title>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
    @media only screen and (max-width: 600px) {
            .login-page {
                width: 360px;
                padding: 40% 0 0;
                margin: auto;
            }
        }
        
        @media only screen and (min-width: 768px) {
            .login-page {
                width: 360px;
                padding: 15% 0 0;
                margin: auto;
            }
        }
        
        .form {
            font-family: "Roboto", serif;
            position: relative;
            z-index: 1;
            border-radius: 5px;
            background: #FFFFFF;
            max-width: 360px;
            margin: 0 auto 100px;
            padding: 45px;
            text-align: center;
            box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 10px 10px 0 rgba(0, 0, 0, 0.24);
        }
        
        body {
            background: #42a5f5;
            /* fallback for old browsers */
        }
    }
    </style>

</head>

<body>
    <div class="login-page">
        <div class="form">
            <form>
                <p style="font-size:25px">Your token number is</p>
                <p style="font-size: 50px; font-weight: 600;">
)=====";
const char tok2[] PROGMEM = R"=====(
</p>
            </form>
        </div>
    </div>
</body>

</html>
)=====";
