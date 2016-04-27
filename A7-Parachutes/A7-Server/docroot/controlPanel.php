<!DOCTYPE html>
<html lang="en" xmlns="http://www.w3.org/1999/xhtml">
<head>
    <link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons">
    <link rel="stylesheet" href="https://code.getmdl.io/1.1.3/material.indigo-pink.min.css">
    <script defer src="https://code.getmdl.io/1.1.3/material.min.js"></script>
    <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
    <script src="res/dialog-polyfill.js"></script>
    <link rel="stylesheet" type="text/css" href="res/dialog-polyfill.css" />
    <meta charset="utf-8" />
    <title>The Lost Boys and Wendy</title>
</head>
<body>
    <div class="mdl-layout mdl-js-layout mdl-layout--fixed-header">
        <header class="mdl-layout__header">
            <div class="mdl-layout__header-row">
                <!-- Title -->
                <span class="mdl-layout-title">Parachute</span>
                <!-- Add spacer, to align navigation to the right -->
                <div class="mdl-layout-spacer"></div>
                <!-- Navigation. We hide it in small screens. -->
                <nav class="mdl-navigation mdl-layout--large-screen-only">                  
                    <a class="mdl-navigation__link" href="index.html">  <button class="mdl-button mdl-js-button mdl-button--raised mdl-js-ripple-effect mdl-button--colored mdl-color--cyan">          Home
                        </button></a>
                    <a class="mdl-navigation__link" href="readme.html">
                        <button class="mdl-button mdl-js-button mdl-button--raised mdl-js-ripple-effect mdl-button--colored mdl-color--cyan">                  README
                        </button>
                    </a>
                    <a class="mdl-navigation__link" href="https://github.com/University-of-Utah-CS3505/u0680482">
                        <button class="mdl-button mdl-js-button mdl-button--raised mdl-js-ripple-effect mdl-button--accent">
                            View This Project
                        </button>
                    </a>
                </nav>
            </div>
        </header>
        <div class="mdl-layout__drawer">
            <span class="mdl-layout-title">Parachute---The Lost Boys & Wendy</span>
            <nav class="mdl-navigation">
                <a class="mdl-navigation__link" href="readme.html">Readme</a>
                <a class="mdl-navigation__link" href="https://github.com/University-of-Utah-CS3505/u0680482">This Project</a>
                <a class="mdl-navigation__link" href="controlPanel.html">Management</a>
                <a class="mdl-navigation__link" href="index.html">Home</a>
            </nav>
        </div>
        <main class="mdl-layout__content">
            <style>
                .demo-card-wide.mdl-card {
                    width: 712px;
                }

                .demo-card-wide > .mdl-card__title {
                    height: 100px;
                    background: url("images/qq.jpg") center / cover;
                }

                .mdl-card__title-text {
                    font-weight: 400;
                    font-size: 26px;
                }

                .demo-card-wide > .mdl-card__menu {
                    color: #fff;
                }

                .my-list {
                    padding: 5px;
                }
            </style>
            <p></p>
            <p></p>
            <p></p>
            <p></p>
            <p></p>
            <p></p>
            <p></p>
            <p></p>
            <center>
                <div class="demo-card-wide mdl-card mdl-shadow--2dp">
                    <div class="mdl-card__title">
                        <h2 class="mdl-card__title-text">Manage Profiles</h2>
                    </div>
                   
                    <div class="mdl-card__supporting-text">
                        <table class="mdl-data-table mdl-js-data-table mdl-data-table--selectable mdl-shadow--2dp">
                            <thead>
                                <tr>
                                    <th class="mdl-data-table__cell--non-numeric">ID</th>
                                    <th>User Name</th>
                                    <th>Score</th>
                                </tr>
                            </thead>
                            <tbody>
                                <tr>
                                    <td class="mdl-data-table__cell--non-numeric">112251</td>
                                    <td>Fred</td>
                                    <td>999</td>
                                </tr>
                                <tr>
                                    <td class="mdl-data-table__cell--non-numeric">1235548</td>
                                    <td>Peter</td>
                                    <td>0</td>
                                </tr>
                                <tr>
                                    <td class="mdl-data-table__cell--non-numeric">2158461</td>
                                    <td>Taner</td>
                                    <td>9999</td>
                                </tr>
                            </tbody>
                        </table>
                        <p></p>
                        <p></p>
                        <button id="remove" class="mdl-button mdl-js-button mdl-button--raised mdl-js-ripple-effect mdl-button--colored">
                           Remove
                        </button>                      
                    </div>
                    <div class="mdl-card__menu">
                        <button class="mdl-button mdl-button--icon mdl-js-button mdl-js-ripple-effect">
                            <i class="material-icons">share</i>
                        </button>
                    </div>
                </div>
            </center>
        </main>
        <footer class="mdl-mini-footer">
            <div class="mdl-mini-footer__left-section">
                <div class="mdl-logo">Parachute Project</div>
                <ul class="my-list mdl-mini-footer__link-list">
                    <li><a href="#">Help</a></li>
                    <li><a href="#">Privacy & Terms</a></li>
                    <li><a href="#">THE LOST BOYS &amp; WENDY ALL RIGHTS RESERVED</a></li>
                </ul>
            </div>
        </footer>
    </div>

    <dialog class="mdl-dialog">
        <h6 class="mdl-dialog__title">Removing</h6>
        <div class="mdl-dialog__content">
            <p>
                Remove the accounts you selected?
            </p>
        </div>
        <div class="mdl-dialog__actions">
            <button type="button" class="mdl-button remove">Remove</button>
            <button type="button" class="mdl-button close">Cancel</button>
        </div>
    </dialog>
    <script>
    var dialog = document.querySelector('dialog');
    var showDialogButton = document.querySelector('#remove');
    if (!dialog.showModal) {
        dialogPolyfill.registerDialog(dialog);
    }
    showDialogButton.addEventListener('click', function () {
      dialog.showModal();
    });
    dialog.querySelector('.close').addEventListener('click', function() {
      dialog.close();
    });
    dialog.querySelector('.remove').addEventListener('click', function() {
      dialog.close();
    });

    </script>
</body>
</html>
