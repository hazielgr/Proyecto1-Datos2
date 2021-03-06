import * as path from 'path';
import * as vscode from 'vscode';


const cats = {
	'Coding Cat': 'https://media.giphy.com/media/JIX9t2j0ZTN9S/giphy.gif',
	'Compiling Cat': 'https://media.giphy.com/media/mlvseq9yvZhba/giphy.gif',
	'Testing Cat': 'https://media.giphy.com/media/3oriO0OEd9QIDdllqo/giphy.gif'
};

export function activate(context: vscode.ExtensionContext) {

	context.subscriptions.push(
		vscode.commands.registerCommand('memoryextension.start', () => {
			CodingPanel.createOrShow(context.extensionPath);
		})
	);
 
	context.subscriptions.push(
		vscode.commands.registerCommand('memoryextension.doRefactor', () => {
			if (CodingPanel.currentPanel) {
				CodingPanel.currentPanel.doRefactor();
			}
		})
	);

	if (vscode.window.registerWebviewPanelSerializer) {
		// Make sure we register a serializer in activation event
		vscode.window.registerWebviewPanelSerializer(CodingPanel.viewType, {
			async deserializeWebviewPanel(webviewPanel: vscode.WebviewPanel, state: any) {
				console.log(`Got state: ${state}`);
				CodingPanel.revive(webviewPanel, context.extensionPath);
			}
		});
	}
}

/**
 * Manages cat coding webview panels
 */
class CodingPanel {
	/**
	 * Track the currently panel. Only allow a single panel to exist at a time.
	 */
	public static currentPanel: CodingPanel | undefined;
	public static readonly viewType = 'Heap Vizualizer';


	private readonly _panel: vscode.WebviewPanel;
	private readonly _extensionPath: string;
	private _disposables: vscode.Disposable[] = [];

	public static createOrShow(extensionPath: string) {
		const column = vscode.window.activeTextEditor
			? vscode.window.activeTextEditor.viewColumn
			: undefined;

		// If we already have a panel, show it.
		if (CodingPanel.currentPanel) {
			CodingPanel.currentPanel._panel.reveal(column);
			return;
		}

		// Otherwise, create a new panel.
		const panel = vscode.window.createWebviewPanel(
			CodingPanel.viewType,
			'Heap Visualizer',
			column || vscode.ViewColumn.One,
			{
				// Enable javascript in the webview
				enableScripts: true,

				// And restrict the webview to only loading content from our extension's `media` directory.
				localResourceRoots: [vscode.Uri.file(path.join(extensionPath, 'media'))]
			}
		);

		CodingPanel.currentPanel = new CodingPanel(panel, extensionPath);
	}

	public static revive(panel: vscode.WebviewPanel, extensionPath: string) {
		CodingPanel.currentPanel = new CodingPanel(panel, extensionPath);
	}

	private constructor(panel: vscode.WebviewPanel, extensionPath: string) {
		
		this._panel = panel;
		this._extensionPath = extensionPath;

		// Set the webview's initial html content
		this._update();

		this.doStuff();
		// Listen for when the panel is disposed
		// This happens when the user closes the panel or when the panel is closed programatically
		this._panel.onDidDispose(() => this.dispose(), null, this._disposables);



		// Update the content based on view changes
		this._panel.onDidChangeViewState(
			e => {
				if (this._panel.visible) {
					this._update();
				}
			},
			null,
			this._disposables
		);



		// Handle messages from the webview
		this._panel.webview.onDidReceiveMessage(
			message => {
				console.log(message.text);
				switch (message.command) {
					case 'settings':
						vscode.window.showErrorMessage(message.text);
						//var result=vsinterface.setClientSettings(message.ip, message.port, message.pass, message.user)
						//this._panel.webview.postMessage({ command: 'status', data:result });
						return;
					case 'alert':
						vscode.window.showErrorMessage(message.text);
						return;
				//	case 'local':
				//		vsinterface.setLocal(true);
				//		return;
				//	case 'remote':
				//		vsinterface.setLocal(false);
				//		return;
				}
			},
			null,
			this._disposables
		);

	}

	public doRefactor() {
		// Send a message to the webview webview.
		// You can send any JSON serializable data.
		this._panel.webview.postMessage({ command: 'refactor' });

	}

	public doStuff(){
	//	setInterval(() => {
	//	
	//		this._panel.webview.postMessage({ command: 'data', data:vsinterface.getUpdate() });
    //  }, 100);
	}

	public dispose() {
		CodingPanel.currentPanel = undefined;

		// Clean up our resources
		this._panel.dispose();

		while (this._disposables.length) {
			const x = this._disposables.pop();
			if (x) {
				x.dispose();
			}
		}
	}

	private _update() {
		const webview = this._panel.webview;

		// Vary the webview's content based on where it is located in the editor.
		switch (this._panel.viewColumn) {
			case vscode.ViewColumn.Two:
				this._updateForCat(webview, 'Compiling Cat');
				return;

			case vscode.ViewColumn.Three:
				this._updateForCat(webview, 'Testing Cat');
				return;

			case vscode.ViewColumn.One:
			default:
				this._updateForCat(webview, 'Coding Cat');
				return;
		}
	}


	private _updateForCat(webview: vscode.Webview, catName: keyof typeof cats) {
		this._panel.title = "Heap Visualizer";
		this._panel.webview.html = this._getHtmlForWebview(webview, cats[catName]);
	}

	private _getHtmlForWebview(webview: vscode.Webview, catGifPath: string) {
		// Local path to main script run in the webview
		const scriptPathOnDisk = vscode.Uri.file(
			path.join(this._extensionPath, 'media', 'main.js')
		);


		// And the uri we use to load this script in the webview
		const scriptUri = webview.asWebviewUri(scriptPathOnDisk);

		// Use a nonce to whitelist which scripts can be run
		const nonce = getNonce();
		return `<!DOCTYPE html>
            <html lang="en">
            <head>
                <meta charset="UTF-8">

                <!--
                Use a content security policy to only allow loading images from https or from our extension directory,
                and only allow scripts that have a specific nonce.
                -->
                <meta http-equiv="Content-Security-Policy" content="default-src 'none'; img-src ${webview.cspSource} https:; script-src 'nonce-${nonce}';">

                <meta name="viewport" content="width=device-width, initial-scale=1.0">
                <title>Heap Visualizer</title>
            </head>
            <body>
                
				<h2>Heap Visualizer </h2>

				<form action="/action_page.php">
					<label for="tipo">Nº---Tipo---</label>
					<label for="valor">Valor---</label>
					<label for="ubicacion">Ubicacion---</label>
					<label for="referencias">Referencias</label><br><br>

					<label id="type">"":</label>
					<label id="val">"":</label>
					<label id="ubi">"":</label>
					<label id="ref">"":</label><br><br>
					
				</form>

					
				<h3>Memoria en uso:</h3>


			

				<input type="radio" id="local" name="settings" value="local" checked="checked">
				<label for="male">Local</label><br>
				<input type="radio" id="remota" name="settings" value="remota" checked="true">
				<label for="female">Remota</label><br>
				
				<h3></h3>

				
				<h3>Conectarse al servidor</h3>
				<form action="/action_page.php">
					<label for="iptext">IP:</label>
					<input type="text" id="ip" name="ip"><br><br>
					<label for="porttext">Puerto:</label>
					<input type="text" id="puerto" name="puerto"><br><br>
					<label for="usertest">Usuario:</label>
					<input type="text" id="usuario" name="usuario"><br><br>
					<label for="passtest">Contraseña:</label>
					<input type="text" id="contraseña" name="contraseña"><br><br>
					<input type="submit" id="setsettings" value="Conectar">
				</form> 

				<h1 id="lines-of-code-counter">0</h1>
                <script nonce="${nonce}" src="${scriptUri}"></script>
            </body>
			</html>`;
		
	}
}

function getNonce() {
	let text = '';
	const possible = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
	for (let i = 0; i < 32; i++) {
		text += possible.charAt(Math.floor(Math.random() * possible.length));
	}
	return text;
}
