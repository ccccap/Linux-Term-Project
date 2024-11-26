<?php
$servername = "localhost";
$username = "dazuoyecccap_com";
$password = "WD3sin3k218MFfpW";
$dbname = "dazuoyecccap_com";

// 创建连接
$conn = new mysqli($servername, $username, $password, $dbname);

// 检测连接
if ($conn->connect_error) {
  die("连接失败: " . $conn->connect_error);
}

// 检查是否有删除请求
if (isset($_GET['delete_id'])) {
    $delete_id = $_GET['delete_id'];
    $sql = "DELETE FROM users WHERE id=$delete_id";

    if ($conn->query($sql) === TRUE) {
        echo "记录删除成功";
    } else {
        echo "删除错误: " . $conn->error;
    }
}

// 查询并显示所有用户
$sql = "SELECT id, username, email, password FROM users";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    echo "<h2>用户列表</h2>";
    echo "<table border='1'>";
    echo "<tr><th>ID</th><th>用户名</th><th>邮箱</th><th>操作</th></tr>";
    while($row = $result->fetch_assoc()) {
        echo "<tr><td>" . $row["id"]. "</td><td>" . $row["username"]. "</td><td>" . $row["email"]. "</td><td><a href='index.php?delete_id=".$row["id"]."'>删除</a></td></tr>";
    }
    echo "</table>";
} else {
    echo "0 结果";
}
$conn->close();
?>

<!DOCTYPE html>
<html>
<head>
    <title>用户注册</title>
</head>
<body>
    <h1>用户注册</h1>
    <form action="index.php" method="post">
        用户名: <input type="text" name="username" required><br>
        邮箱: <input type="email" name="email" required><br>
        密码: <input type="password" name="password" required><br>
        <input type="submit" name="submit" value="注册">
    </form>

    <?php
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        if (isset($_POST['submit'])) {
            $username = $_POST['username'];
            $email = $_POST['email'];
            $password = password_hash($_POST['password'], PASSWORD_DEFAULT);

            $sql = "INSERT INTO users (username, email, password) VALUES ('$username', '$email', '$password')";

            if ($conn->query($sql) === TRUE) {
                echo "新记录插入成功";
            } else {
                echo "错误: " . $conn->error;
            }
        }
    }
    ?>
</body>
</html>